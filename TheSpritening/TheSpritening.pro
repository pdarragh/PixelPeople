#-------------------------------------------------
#
# Project created by QtCreator 2015-11-01T13:13:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheSpritening
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sprite.cpp \
    fullpreview.cpp

HEADERS  += mainwindow.h \
    sprite.h \
    fullpreview.h

FORMS    += mainwindow.ui \
    fullpreview.ui

RESOURCES += \
    resources.qrc
