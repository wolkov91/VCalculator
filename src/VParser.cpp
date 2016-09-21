#include "VParser.h"
#include <algorithm>

using namespace VCalc;

void VParser::reset(const std::string &expression)
{
    m_previousTokenType = VToken::Type::LeftBracket;
    m_positionOffset = 0;
    m_expression = expression;
}

void VParser::skipSpaces()
{
    for (const size_t length = m_expression.length(); m_positionOffset < length; ++m_positionOffset)
    {
        if (m_expression[m_positionOffset] != SPACE)    // можно использовать std::isspace(character, locale)
            break;
    }
}

VToken *VParser::parseNextToken()
{
    skipSpaces();

    if (m_positionOffset >= m_expression.size()) {
        return nullptr;
    }

    VToken *token = nullptr;

    switch (m_previousTokenType) {
    case VToken::Type::LeftBracket: {
        token = parseLeftBracket();
        if (token)
            return token;
        token = parseOperand();
        if (token)
            return token;
    } break;
    case VToken::Type::RightBracket: {
        token = parseRightBracket();
        if (token)
            return token;
        token = parseOperator();
        if (token)
            return token;
    } break;
    case VToken::Type::Operator: {
        token = parseLeftBracket();
        if (token)
            return token;
        token = parseOperand();
        if (token)
            return token;
    } break;
    case VToken::Type::Operand: {
        token = parseLeftBracket();
        if (token)
            return token;
        token = parseRightBracket();
        if (token)
            return token;
        token = parseOperator();
        if (token)
            return token;
    } break;
    default:
        break;
    }

    throw std::runtime_error("Incorrect input: Uncnown character '"
                             + std::string(1, m_expression.at(m_positionOffset))
                             + "' in position " + std::to_string(m_positionOffset)
                             );
}

VToken *VParser::parseLeftBracket()
{
    char character = m_expression.at(m_positionOffset);
    if (character == '(') {
        ++m_positionOffset;
        m_previousTokenType = VToken::Type::LeftBracket;
        return new VToken(m_previousTokenType, std::string(1, character));
    }
    return nullptr;
}

VToken *VParser::parseRightBracket()
{
    char character = m_expression.at(m_positionOffset);
    if (character == ')') {
        ++m_positionOffset;
        m_previousTokenType = VToken::Type::RightBracket;
        return new VToken(m_previousTokenType, std::string(1, character));
    }
    return nullptr;
}

VToken *VParser::parseOperand() //TODO: Поменять на регулярки!
{
//    char character = m_expression.at(m_positionOffset);
//    if (character == '-' || std::isdigit(character)) {
//        m_previousTokenType = VToken::Type::Operand;
//        std::size_t signatureLendht;
//        std::stod(m_expression.substr(m_positionOffset), &signatureLendht);
//        std::string signature = m_expression.substr(m_positionOffset, signatureLendht);
//        m_positionOffset += signatureLendht;
//        return new VOperandToken(signature);
//    }
//    return nullptr;


//    std::string doubleRE = "\\-?\\d{1,7}([\\.|\\,]\\d{1,2})";
    char character = m_expression.at(m_positionOffset);
    size_t oldPos = m_positionOffset;
    int digitCountBeforeDot = 0;
    int digitCountAfterDot = 0;

    enum st {
        MINUS,
        BEFORE,
        DOT,
        AFTER,
        FINISH
    } status;

    if (character == '-') {
        status = MINUS;
        if (m_positionOffset + 1 >= m_expression.size()) {
            throw std::runtime_error("Incorrect input: '-' in position " + std::to_string(oldPos));
        }
    } else if (std::isdigit(character)) {
        status = BEFORE;
        ++digitCountBeforeDot;
    } else {
        return nullptr;
    }

    while (status != FINISH && ++m_positionOffset < m_expression.size() /*&& status != ERROR*/) {
//        ++m_positionOffset;
        character = m_expression.at(m_positionOffset);

        switch (status) {
        case MINUS: {
            if (std::isdigit(character)) {
                status = BEFORE;
                ++digitCountBeforeDot;
            } else {
                throw std::runtime_error("Incorrect input: '-' in position " + std::to_string(oldPos));
            }
        } break;
        case BEFORE: {
            if (std::isdigit(character)) {
                ++digitCountBeforeDot;
                if (digitCountBeforeDot > 7) {
					throw std::runtime_error("Incorrect input: absolute value of the number greater than 10 000 000 in position "
                                          + std::to_string(oldPos));
                }
            } else if (character == '.' || character == ',') {
                status = DOT;
            } else {
                status = FINISH;
            }
        } break;
        case DOT: {
            if (std::isdigit(character)) {
                status = AFTER;
                ++digitCountAfterDot;
            } else {
                throw std::runtime_error("Incorrect input: '" + std::string(1, character)
                                         + "' in position " + std::to_string(oldPos));
            }
        } break;
        case AFTER: {
            if (std::isdigit(character)) {
                ++digitCountAfterDot;
                if (digitCountAfterDot > 2) {
                    throw std::runtime_error("Incorrect input: the number of digits after the decimal point is greater than 2 in position "
                                         + std::to_string(m_positionOffset));
                }
            } else {
                status = FINISH;
            }
        } break;
        }
    }

    m_previousTokenType = VToken::Type::Operand;
    std::string signature = m_expression.substr(oldPos, m_positionOffset - oldPos);
    return new VOperandToken(signature);
}

VToken *VParser::parseOperator()
{
    char character = m_expression.at(m_positionOffset);
    const std::vector<char> operators = VOperatorToken::getSignaturesOfSupportedOperators();
    auto findIterator = std::find(operators.begin(), operators.end(), character);
    if (findIterator != operators.end()) {
        ++m_positionOffset;
        m_previousTokenType = VToken::Type::Operator;
        return new VOperatorToken(std::string(1, character));
    }
    return nullptr;
}
