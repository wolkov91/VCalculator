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
#ifndef VOPERATORTOKEN_H
#define VOPERATORTOKEN_H

#include "VToken.h"

namespace VCalc
{

///
/// \brief The VOperatorToken class - токен операторов сложения, вычитания, умножения и деления.
///
class VOperatorToken : public VToken
{
public:
    ///
    /// \brief The Priority enum - приоритеты операторов.
    ///
    enum Priority {
        PriorityOperatorAdd = 100,
        PriorityOperatorSub = PriorityOperatorAdd,
        PriorityOperatorMul = 200,
        PriorityOperatorDiv = PriorityOperatorMul
    };

    ///
    /// \brief The Associativity enum - виды ассоциативностей операторов.
    ///
    enum class Associativity {
        Left
    };

    VOperatorToken(const std::string &signature);

    ~VOperatorToken() override = default;

    static const std::vector<char> getSignaturesOfSupportedOperators();

    unsigned int getArgumentsCount() const { return m_argumentsCount; }
    int getPriority() const { return m_priority; }
    Associativity getAssociativity() const { return m_associativity; }

    bool isLeftAssociative() const { return m_associativity == Associativity::Left; }

    ///
    /// \brief compute - вычислить значение действия оператора.
    /// \param args - стэк аргументов действия. Первый (левый) аргумент находится в вершине стэка.
    /// Количество аргументов должно совпадать с getArgumentsCount().
    /// \return значение действия.
    ///
    double compute(const std::vector<double> &args);

private:
    unsigned int m_argumentsCount;
    int m_priority;
    Associativity m_associativity;
};

} //namespace

#endif // VOPERATORTOKEN_H
