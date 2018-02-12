#-------------------------------------------------
#
# Project created by QtCreator 2017-12-12T22:05:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myqq
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    toolbox.cpp

HEADERS  += widget.h \
    toolbox.h

FORMS    += widget.ui \
    widget.ui

RESOURCES += \
    image.qrc
