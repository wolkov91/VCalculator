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
#ifndef VOPERANDTOKEN_H
#define VOPERANDTOKEN_H

#include "VToken.h"
#include <cassert>

namespace VCalc
{

///
/// \brief The VOperandToken class - токен-операнд, хранящий значение типа double.
///
class VOperandToken : public VToken
{
public:
    VOperandToken(const std::string &signature)
        : VToken(Type::Operand, signature)
    {
        size_t end;
        std::string tempSign = signature;
        for (int i = tempSign.size(); i > -1; --i) {
            if (tempSign[i] == ',') {
                tempSign[i] = '.';
                break;
            }
        }
        m_value = std::stod(tempSign, &end);
        assert(end == signature.size());
    }

    ~VOperandToken() override = default;

    double getValue() const { return m_value; }

private:
    double m_value;
};

} //namespace

#endif // VOPERANDTOKEN_H
