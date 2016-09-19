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
#ifndef VPARSER_H
#define VPARSER_H

#include "VOperandToken.h"
#include "VOperatorToken.h"

#include <memory>

namespace VCalc
{

///
/// \brief The VParser class - выполняет роль лексического анализатора.
///
class VParser
{
public:
    VParser() = default;
    ~VParser() = default;

    ///
    /// \brief reset - сбросить в исходное состояние и задать новое выражение для обработки.
    /// \param expression - математическое выражение.
    ///
    void reset(const std::string &expression);

    ///
    /// \brief parseNextToken - пока выражение полностью не обработано, выделяет следующий токен.
    /// При некорректном выражении вызывает исключения std::runtime_error.
    /// \return указатель на токен или nullptr.
    ///
    VToken *parseNextToken();

private:
    void skipSpaces();
    VToken *parseLeftBracket();
    VToken *parseRightBracket();
    VToken *parseOperand();
    VToken *parseOperator();

private:
    static const char SPACE = ' ';

    VToken::Type m_previousTokenType;
    std::string m_expression;
    size_t m_positionOffset;
};

} //namespace

#endif // VPARSER_H
