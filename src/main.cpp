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

#include "VCalculator.h"
#include <iostream>

int main(int argc, char *argv[])
{
    //setlocale(LC_ALL, "rus");
	if (argc < 2) {
        std::cout << "Is absent expression!";
        return 1;
    }
    VCalc::VCalculator calculator;
    double ret;
    try {
		ret = calculator.calculate(argv[1]);
        std::cout << ret << std::endl;
    } catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
