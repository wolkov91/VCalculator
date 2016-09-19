/*
 * This file is part of VCalculator.
 * VCalculator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Autor is Volkov Semyon.
 */
#ifndef VTOKEN_H
#define VTOKEN_H

#include <string>
#include <vector>

namespace VCalc
{

///
/// \brief The VToken class - токен.
///
class VToken
{
public:
    ///
    /// \brief The TokenType enum class - поддерживаемые типы токенов.
    ///
    enum class Type
    {
        LeftBracket,
        RightBracket,
        Operand,
        Operator
    };

public:
    //VAbstractToken() = delete;
    VToken(const Type &type, const std::string &signature)
        : m_type(type)
        , m_signature(signature)
    {}

    virtual ~VToken() = default;

    bool isLeftBracket() const { return m_type == Type::LeftBracket; }
    bool isRightBracket() const { return m_type == Type::RightBracket; }
    bool isOperand() const { return m_type == Type::Operand; }
    bool isOperator() const { return m_type == Type::Operator; }

    Type getType() const { return m_type; }
    std::string getSignature() const { return m_signature; }

private:
    Type m_type;
    std::string m_signature;
};

} //namespace

#endif // VTOKEN_H
