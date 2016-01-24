#-------------------------------------------------
#
# Project created by QtCreator 2016-01-21T18:25:24
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheTank
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameengine.cpp \
    tmxfiles.cpp \
    tank.cpp \
    tankcontrolerbutton.cpp

HEADERS  += mainwindow.h \
    gameengine.h \
    tmxfiles.h \
    tank.h \
    tankcontrolerbutton.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources.qrc

