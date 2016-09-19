#-------------------------------------------------
#
# Project created by QtCreator 2016-09-15T22:30:38
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

CONFIG += c++11

TARGET = tests #Test_VCalculator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../src/

SOURCES += \
    main.cpp \
    Test_VCalculator.cpp \
    Test_VParser.cpp \
    Test_VOperandToken.cpp \
    Test_VOperatorToken.cpp \
    ../src/VCalculator.cpp \
    ../src/VOperatorToken.cpp \
    ../src/VParser.cpp

HEADERS += \
    Test_VCalculator.h \
    Test_VParser.h \
    Test_VOperandToken.h \
    Test_VOperatorToken.h \
    ../src/VCalculator.h \
    ../src/VToken.h \
    ../src/VOperandToken.h \
    ../src/VOperatorToken.h \
    ../src/VToken.h \
    ../src/VParser.h

##install:
#target.path = ../build/tests
#INSTALLS += target
