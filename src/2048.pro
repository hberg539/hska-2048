#-------------------------------------------------
#
# Project created by QtCreator 2016-11-04T20:34:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2048
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    core/Board.cpp \
    core/Tile.cpp \
    core/Game.cpp

HEADERS  += mainwindow.h \
    core/Board.h \
    core/Tile.h \
    Definitions.h \
    core/Game.h

FORMS    += mainwindow.ui
