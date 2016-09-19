#include "VOperatorToken.h"
#include <stdexcept>

using namespace VCalc;

VOperatorToken::VOperatorToken(const std::string &signature)
    : VToken(Type::Operator, signature)
    , m_argumentsCount(2)
    , m_associativity(Associativity::Left)
{
    if (signature == "+") {
        m_priority = PriorityOperatorAdd;
    } else if (signature == "-") {
        m_priority = PriorityOperatorSub;
    } else if (signature == "*") {
        m_priority = PriorityOperatorMul;
    } else if (signature == "/") {
        m_priority = PriorityOperatorDiv;
    } else {
        throw std::invalid_argument("Invalid signature value '" + signature +
                                    "' in VOperatorToken::VOperatorToken(const std::string &)");
    }
}

const std::vector<char> VOperatorToken::getSignaturesOfSupportedOperators()
{
    return {'+', '-', '*', '/'};
}

double VOperatorToken::compute(const std::vector<double> &args)
{
    if (args.size() != getArgumentsCount()) {
        throw std::invalid_argument("Invalid arguments count " + std::to_string(args.size()));
    }

    std::string signature = getSignature();
    if (signature == "+") {
        return args.at(1) + args.at(0);
    } else if (signature == "-") {
        return args.at(1) - args.at(0);
    } else if (signature == "*") {
        return args.at(1) * args.at(0);
    } else if (signature == "/") {
        return args.at(1) / args.at(0);
    }
    throw std::invalid_argument("Invalid signature value '" + signature +
                                "' in VOperatorToken::compute(const std::vector<double> &)");
}
