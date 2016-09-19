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
#ifndef TEST_VCALCULATOR_H
#define TEST_VCALCULATOR_H

#include <QtTest>
#include <QString>
#include "VCalculator.h"

namespace VCalc
{

class Test_VCalculator : public QObject
{
    Q_OBJECT
public:
    explicit Test_VCalculator(QObject *parent = 0);

private slots:
//    void initTestCase();
//    void cleanupTestCase();
//    void init();
//    void cleanup();
    void calculate_data();
    void calculate();

    void calculate_throwException_data();
    void calculate_throwException();

    void round_data();
    void round();

private:
    VCalculator m_calc;
};

} //namespace

#endif // TEST_VCALCULATOR_H
