#include "Test_VCalculator.h"

using namespace VCalc;

Test_VCalculator::Test_VCalculator(QObject *parent)
    : QObject(parent)
{}

void Test_VCalculator::calculate_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<double>("expected");

    QTest::newRow("#00") << "0" << 0.; // +1
    QTest::newRow("#01") << "-1 + 5 - 3" << 1.;
    QTest::newRow("#02") << "-10 + (8 * 2.5) - (3 / 1,5)" << 8.;
    QTest::newRow("#03") << "1 + ( 2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)" << 11.;
    QTest::newRow("round #01") << "-0.11 * (-0,11)" << 0.01;
    QTest::newRow("round #02") << "-0.11 * 0,11" << -0.01;
    QTest::newRow("#04") << "1 + ( 2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)" << 11.;
}

void Test_VCalculator::calculate()
{
    QFETCH(QString, expression);
    QFETCH(double, expected);

    std::string expr = expression.toStdString();
    double actual = m_calc.calculate(expr);

    //TODO: Для 0.0 надо использовать qFuzzyCompare(1 + 0.0, 1 + 1.0e-200);
    QCOMPARE(actual, expected);
}

void Test_VCalculator::calculate_throwException_data()
{
    QTest::addColumn<QString>("expression");

    QTest::newRow("expression is empty")        << "";
    QTest::newRow("expression is 1.111")        << "1.111";
    QTest::newRow("expression is 10 000")       << "10 000";
    QTest::newRow("expression is 10000001")     << "10000001";
    QTest::newRow("expression is 10000000.1")   << "10000000.1";
    QTest::newRow("expression is .5")           << ".5";
    QTest::newRow("missing operand")            << "0-";
    QTest::newRow("missing '('")                << "2*5)";
    QTest::newRow("missing ')'")                << "(2*5";
    QTest::newRow("unknown symbol")             << "1.1 + 2.1 + abc";
}

void Test_VCalculator::calculate_throwException()
{
    QFETCH(QString, expression);

    std::string expr = expression.toStdString();

    QVERIFY_EXCEPTION_THROWN(m_calc.calculate(expr), std::exception);
}

void Test_VCalculator::round_data()
{
    QTest::addColumn<double>("value");
    QTest::addColumn<int>("precision");
    QTest::addColumn<double>("expected");

    QTest::newRow("0.1")   << 0.12345  << 1 << 0.1;
    QTest::newRow("0.9")   << 0.88     << 1 << 0.9;
    QTest::newRow("0.12")  << 0.12345  << 2 << 0.12;
    QTest::newRow("0.123") << 0.12345  << 3 << 0.123;
    QTest::newRow("0.9")   << 0.12345  << 3 << 0.123;
    QTest::newRow("-0.12") << -0.12345 << 2 << -0.12;
    QTest::newRow("-55.12346") << -55.123456789 << 5 << -55.12346;
}

void Test_VCalculator::round()
{
    QFETCH(double, value);
    QFETCH(int, precision);
    QFETCH(double, expected);

    double actual = m_calc.round(value, precision);

    QCOMPARE(actual, expected);
}
