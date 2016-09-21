#include "VCalculator.h"
#include "VParser.h"
#include <cassert>
#include <algorithm>

using namespace VCalc;

std::vector<std::unique_ptr<VToken>> VCalculator::buildPostfixNotation(const std::string &expression)
{
    std::vector<std::unique_ptr<VToken>> outputVector;
    std::vector<std::unique_ptr<VToken>> stack;

    m_parser.reset(expression);
    std::unique_ptr<VToken> token(m_parser.parseNextToken());
    for (; token.get() != nullptr; token.reset(m_parser.parseNextToken())) {

        switch (token->getType()) {
        case VToken::Type::Operand:
            //Помещаем в очередь вывода
            outputVector.push_back(std::move(token));
            break;
        case VToken::Type::Operator:
        {
            VOperatorToken * operatorPtr = dynamic_cast<VOperatorToken *>(token.release());
            std::unique_ptr<VOperatorToken> operatorToken(operatorPtr);
            int operatorPriority = operatorToken->getPriority();
            while (!stack.empty()
                   && stack.back()->isOperator()
                   && ((
                           operatorToken->isLeftAssociative()
                           && operatorPriority <= dynamic_cast<VOperatorToken*>(stack.back().get())->getPriority()
                       ) /*|| (
                           operatorToken->isRightAssociative()
                           && operatorPriority < dynamic_cast<VOperatorToken*>(stack.back())->getPriority())*/
                       )
                   ) {
                //Перемещаем из стэка в очередь вывода
                outputVector.push_back(std::move(stack.back()));
                stack.pop_back();
            }
            //Помещаем оператор в стэк
            stack.push_back(std::move(operatorToken));
        }
            break;
        case VToken::Type::LeftBracket:
            //Помещаем во временный стэк
            stack.push_back(std::move(token));
            break;
        case VToken::Type::RightBracket:
        {
            while (!stack.empty()
                   && !stack.back()->isLeftBracket()) {
                //Перемещаем из стэка в очередь вывода
                outputVector.push_back(std::move(stack.back()));
                stack.pop_back();
            }
            if (stack.empty()) {
				throw std::runtime_error("Incorrect input: unpaired closing bracket is present in the expression.");
            }
            //Удаляем открывающую скобку
            stack.pop_back();
            //Удаляем закрывающую скобку
            token.reset();
        }
            break;
        default:
            assert(false); // Должно всегда срабатывать в режиме отладки
            break;
        }
    }

    while (!stack.empty()) {
        if (stack.back()->isLeftBracket()) {
			throw std::runtime_error("Incorrect input: not a closed bracket is present in the expression.");
        }
        //Перемещаем из стэка в очередь вывода
        outputVector.push_back(std::move(stack.back()));
        stack.pop_back();
    }

    return outputVector;
}

double VCalculator::VCalculator::calculate(const std::string &expression)
{
    if (expression.empty()) {
        throw std::runtime_error("Incorrect input: expression is empty.");
    }

    std::vector<double> outputStack;
    //reversr polish notation
    std::vector<std::unique_ptr<VToken>> rpnStack = std::move(buildPostfixNotation(expression));

    std::reverse(rpnStack.begin(), rpnStack.end());

    while (!rpnStack.empty()) {
        switch (rpnStack.back()->getType()) {
        case VToken::Type::Operand: {
            VOperandToken * operandPtr = dynamic_cast<VOperandToken *>(rpnStack.back().release());
            std::unique_ptr<VOperandToken> operand(operandPtr);
            rpnStack.pop_back();
            outputStack.push_back(operand->getValue());
        } break;
        case VToken::Type::Operator: {
            VOperatorToken * actionPtr = dynamic_cast<VOperatorToken *>(rpnStack.back().release());
            std::unique_ptr<VOperatorToken> action(actionPtr);
            rpnStack.pop_back();
            unsigned int argsCount = action->getArgumentsCount();
            if (outputStack.size() < argsCount) {
				throw std::runtime_error("Incorrect input: not enough arguments.");
            }
            std::vector<double> args;
            for (unsigned int i = 0; i < argsCount; ++i) {
                args.push_back(outputStack.back());
                outputStack.pop_back();
            }
            double value = action->compute(args);
            outputStack.push_back(value);
            args.clear();
        } break;
        default:
            assert(false);
            break;
        }
    }
    double ret = outputStack.back();
    assert(outputStack.size() == 1);
	outputStack.clear();
    const int precision = 2;
    return round(ret, precision);
}

double VCalculator::round(double value, int precision) const
{
    int mul = 1;
    for (int i = 0; i < precision; i++)
       mul *= 10;

    if (value > 0)
       return floor(value * mul + .5) / mul;
    else
       return ceil(value * mul - .5) / mul;
}
