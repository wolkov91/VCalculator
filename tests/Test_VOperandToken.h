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
#ifndef TEST_VOPERANDTOKEN_H
#define TEST_VOPERANDTOKEN_H

#include <QtTest>
#include <QString>
#include "VOperandToken.h"

namespace VCalc
{

class Test_VOperandToken : public QObject
{
    Q_OBJECT
public:
    explicit Test_VOperandToken(QObject *parent = 0);

private slots:
//    void initTestCase();
//    void cleanupTestCase();
//    void init();
//    void cleanup();
    void constructor_data();
    void constructor();
};

} //namespace

#endif // TEST_VOPERANDTOKEN_H
