#include "Test_VOperatorToken.h"
#include "VOperatorToken.h"

using namespace VCalc;

Test_VOperatorToken::Test_VOperatorToken(QObject *parent)
    : QObject(parent)
{}

void VCalc::Test_VOperatorToken::compute_data()
{
    QTest::addColumn<QString>("signature");
    QTest::addColumn<std::vector<double>>("args");
    QTest::addColumn<double>("value");

    QTest::newRow("22.2 + 7.8") << "+" << std::vector<double>({7.8, 22.2}) << 30.;
    QTest::newRow("30.0 - 7.8") << "-" << std::vector<double>({7.8, 30.}) << 22.2;
    QTest::newRow("22.2 * 100") << "*" << std::vector<double>({100, 22.2}) << 2220.;
    QTest::newRow("101 / 10.1") << "/" << std::vector<double>({10.1, 101}) << 10.;
}

void VCalc::Test_VOperatorToken::compute()
{
    QFETCH(QString, signature);
    QFETCH(std::vector<double>, args);
    QFETCH(double, value);

    std::string expectedSignature = signature.toStdString();
    VOperatorToken token(expectedSignature);
    double actualValue = token.compute(args);

    QCOMPARE(actualValue, value);
}
