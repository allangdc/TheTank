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
    tankcontrolerbutton.cpp \
    game_map.cpp \
    game_tile.cpp \
    game_tiled_set.cpp \
    game_tmx_map.cpp \
    game_map_layer.cpp

HEADERS  += mainwindow.h \
    gameengine.h \
    tmxfiles.h \
    tank.h \
    tankcontrolerbutton.h \
    game_map.h \
    game_tile.h \
    game_tiled_set.h \
    game_tmx_map.h \
    game_map_layer.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources.qrc
