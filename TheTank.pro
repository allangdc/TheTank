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
    controller/tankcontrolerbutton.cpp \
    map/game_map.cpp \
    map/game_tile.cpp \
    map/game_tiled_set.cpp \
    map/game_tmx_map.cpp \
    map/game_map_layer.cpp \
    vehicle/vehicle.cpp \
    map/game_camera.cpp \
    map/game_tile_colision.cpp \
    objects/bomb.cpp \
    objects/tank.cpp

HEADERS  += mainwindow.h \
    gameengine.h \
    controller/tankcontrolerbutton.h \
    map/game_map.h \
    map/game_tile.h \
    map/game_tiled_set.h \
    map/game_tmx_map.h \
    map/game_map_layer.h \
    vehicle/vehicle.h \
    map/game_camera.h \
    map/game_tile_colision.h \
    objects/bomb.h \
    objects/tank.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources.qrc

