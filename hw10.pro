#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T22:30:45
#
#-------------------------------------------------

QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hw8
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp

HEADERS  += mainwindow.h \
    gameboard.h \
    Documentation.h

FORMS    += mainwindow.ui \
    gameboard.ui

RESOURCES += \
    Images.qrc

QMAKE_CXXFLAGS += -std=c++11
