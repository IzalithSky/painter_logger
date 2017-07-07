#-------------------------------------------------
#
# Project created by QtCreator 2017-07-06T11:26:25
#
#-------------------------------------------------

QT       -= gui

TARGET = logic
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    painterlogic.cpp \
    actionlogger.cpp \
    cursor.cpp

HEADERS += \
    painterlogic.h \
    actionlogger.h \
    cursor.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
