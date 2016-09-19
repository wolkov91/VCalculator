#include "Test_VOperandToken.h"

using namespace VCalc;

Test_VOperandToken::Test_VOperandToken(QObject *parent)
    : QObject(parent)
{}

void Test_VOperandToken::constructor_data()
{
    QTest::addColumn<QString>("signature");
    QTest::addColumn<double>("value");

    QTest::newRow("-10.0") << "-10.0" << -10.;
    QTest::newRow("-10,0") << "-10,0" << -10.;
    QTest::newRow("10.55") << "10.55" << 10.55;
    QTest::newRow("10") << "10" << 10.;
    QTest::newRow("9 999 999") << "9999999" << 9999999.;
}

void Test_VOperandToken::constructor()
{
    QFETCH(QString, signature);
    QFETCH(double, value);

    std::string expectedSignature = signature.toStdString();
    VOperandToken token(expectedSignature);
    std::string actualSignature = token.getSignature();
    double actualValue = token.getValue();
    VToken::Type actualType = token.getType();

    QCOMPARE(actualSignature, expectedSignature);
    QCOMPARE(actualValue, value);
    QCOMPARE(actualType, VToken::Type::Operand);
}
