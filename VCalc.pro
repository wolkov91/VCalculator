QT += core
QT -= gui

CONFIG += c++11

TARGET = vcalc
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += src/

SOURCES += \
    src/main.cpp \
    src/VCalculator.cpp \
    src/VOperatorToken.cpp \
    src/VParser.cpp

HEADERS += \
    src/VCalculator.h \
    src/VOperandToken.h \
    src/VOperatorToken.h \
    src/VParser.h \
    src/VToken.h
