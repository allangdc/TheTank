#-------------------------------------------------
#
# Project created by QtCreator 2016-01-21T18:25:24
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheTank
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameengine.cpp \
    controller/tank_controler_button.cpp \
    map/game_map.cpp \
    map/game_tile.cpp \
    map/game_tiled_set.cpp \
    map/game_tmx_map.cpp \
    map/game_map_layer.cpp \
    vehicle/vehicle.cpp \
    map/game_camera.cpp \
    map/game_tile_colision.cpp \
    objects/bomb.cpp \
    objects/tank.cpp \
    connection/game_client.cpp \
    connection/game_server.cpp \
    connection/game_socket.cpp \
    connection/game_protocol.cpp \
    connection/ipconfigdialog.cpp

HEADERS  += mainwindow.h \
    gameengine.h \
    controller/tank_controler_button.h \
    map/game_map.h \
    map/game_tile.h \
    map/game_tiled_set.h \
    map/game_tmx_map.h \
    map/game_map_layer.h \
    vehicle/vehicle.h \
    map/game_camera.h \
    map/game_tile_colision.h \
    objects/bomb.h \
    objects/tank.h \
    connection/game_client.h \
    connection/game_server.h \
    connection/game_socket.h \
    connection/game_protocol.h \
    connection/ipconfigdialog.h

FORMS    += mainwindow.ui \
    connection/ipconfigdialog.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources.qrc

