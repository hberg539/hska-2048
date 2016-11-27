#-------------------------------------------------
#
# Project created by QtCreator 2016-11-04T20:34:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2048
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    gui/qtile.cpp \
    gui/qboard.cpp \
    core/board.cpp \
    core/game.cpp \
    core/tile.cpp \
    solver.cpp \
    newgame.cpp \
    qsolver.cpp

HEADERS  += mainwindow.h \
    Definitions.h \
    gui/qtile.h \
    gui/qboard.h \
    core/board.h \
    core/game.h \
    core/tile.h \
    solver.h \
    newgame.h \
    qsolver.h

FORMS    += mainwindow.ui \
    solver.ui \
    newgame.ui

DISTFILES += \
