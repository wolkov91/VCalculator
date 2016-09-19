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
#include <QTest>

#include "Test_VCalculator.h"
#include "Test_VParser.h"
#include "Test_VOperandToken.h"
#include "Test_VOperatorToken.h"

using namespace VCalc;

int main(int argc, char *argv[])
{
    int testReturnCode;
    bool success = true;

    Test_VOperandToken operandToken;
    testReturnCode = QTest::qExec(&operandToken, argc, argv);
    success = success && (testReturnCode == 0);

    Test_VOperatorToken operatorToken;
    testReturnCode = QTest::qExec(&operatorToken, argc, argv);
    success = success && (testReturnCode == 0);

    Test_VParser parser;
    testReturnCode = QTest::qExec(&parser, argc, argv);
    success = success && (testReturnCode == 0);

    Test_VCalculator calculator;
    testReturnCode = QTest::qExec(&calculator, argc, argv);
    success = success && (testReturnCode == 0);

    return success ? 0 : 1;
}
