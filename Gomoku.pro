#-------------------------------------------------
#
# Project created by QtCreator 2011-05-12T22:22:53
#
#-------------------------------------------------

QT       += core gui

TARGET = Gomoku
TEMPLATE = app

INCLUDEPATH += ./inc

SOURCES += ./src/main.cpp\
        ./src/APlayer.cpp\
        ./src/Board.cpp\
        ./src/Game.cpp\
        ./src/HPlayer.cpp\
        ./src/mainwindow.cpp\
        ./src/Referee.cpp\
        ./src/Square.cpp \
        ./src/gridmanager.cpp


HEADERS  += ./inc/mainwindow.hpp

FORMS    += ./forms/mainwindow.ui

RESOURCES += \
    ressources/texture.qrc
