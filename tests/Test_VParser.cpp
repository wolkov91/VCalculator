#include "Test_VParser.h"

using namespace VCalc;

Q_DECLARE_METATYPE(VCalc::VToken::Type)

Test_VParser::Test_VParser(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<VCalc::VToken::Type>();
}

void Test_VParser::initTestCase()
{
    m_parser.reset("-10.0 +((8*    2.5 )-( 3 /1,55))");
}

void Test_VParser::parseNextToken_data()
{
    QTest::addColumn<QString>("signature");
    QTest::addColumn<VCalc::VToken::Type>("type");

    QTest::newRow("#01") << "-10.0" << VCalc::VToken::Type::Operand;
    QTest::newRow("#02") << "+"     << VCalc::VToken::Type::Operator;
    QTest::newRow("#03") << "(" << VCalc::VToken::Type::LeftBracket;
    QTest::newRow("#04") << "(" << VCalc::VToken::Type::LeftBracket;
    QTest::newRow("#05") << "8" << VCalc::VToken::Type::Operand;
    QTest::newRow("#06") << "*" << VCalc::VToken::Type::Operator;
    QTest::newRow("#07") << "2.5" << VCalc::VToken::Type::Operand;
    QTest::newRow("#08") << ")" << VCalc::VToken::Type::RightBracket;
    QTest::newRow("#09") << "-" << VCalc::VToken::Type::Operator;
    QTest::newRow("#10") << "(" << VCalc::VToken::Type::LeftBracket;
    QTest::newRow("#11") << "3" << VCalc::VToken::Type::Operand;
    QTest::newRow("#12") << "/" << VCalc::VToken::Type::Operator;
    QTest::newRow("#13") << "1,55" << VCalc::VToken::Type::Operand;
    QTest::newRow("#14") << ")" << VCalc::VToken::Type::RightBracket;
    QTest::newRow("#15") << ")" << VCalc::VToken::Type::RightBracket;
}

void Test_VParser::parseNextToken()
{
    QFETCH(QString, signature);
    QFETCH(VCalc::VToken::Type, type);

    std::string expectedSignature = signature.toStdString();
    VToken *token = m_parser.parseNextToken();
    std::string actualSignature = token->getSignature();
    VToken::Type actualType = token->getType();

    QCOMPARE(actualSignature, expectedSignature);
    QCOMPARE(actualType, type);

    delete token;
}
