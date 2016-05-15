#-------------------------------------------------
#
# Project created by QtCreator 2016-05-13T16:18:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = TaikoDrumMaster
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    taiko.cpp \
    drumeffect.cpp \
    drum.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    taiko.h \
    drumeffect.h \
    drum.h \
    dialog.h

FORMS    += mainwindow.ui

RESOURCES += \
    taiko_pic.qrc
