#-------------------------------------------------
#
# Project created by QtCreator 2019-11-21T01:36:30
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Message_Box
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    logintest.cpp

HEADERS  += widget.h \
    logintest.h

FORMS    += widget.ui
CONFIG += C++11

RESOURCES += \
    image.qrc
