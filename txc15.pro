#-------------------------------------------------
#
# Project created by QtCreator 2014-06-14T17:01:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = txc15
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        txcmain.cpp \
    txledlight.cpp \
    txcdatabase.cpp

HEADERS  += txcmain.h \
    txledlight.h \
    txcdatabase.h \
    txcdef.h

FORMS    += txcmain.ui

RESOURCES += \
    txc15Res.qrc

TRANSLATIONS = txlg_en.ts \
    txlg_zh_TW.ts \
    txlg_ru.ts

VERSION = 15.0.619
#CONFIG += uitools
