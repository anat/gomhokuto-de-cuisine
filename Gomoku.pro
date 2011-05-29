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
        ./src/gridmanager.cpp \
    src/parameters.cpp

HEADERS  += ./inc/mainwindow.hpp \
    ./inc/Types.hpp \
    ./inc/Square.hpp \
    ./inc/Referee.hpp \
    ./inc/HPlayer.hpp \
    ./inc/gridmanager.hpp \
    ./inc/Game.hpp \
    ./inc/Board.hpp \
    ./inc/APlayer.hpp \
    inc/parameters.hpp

FORMS    += ./forms/mainwindow.ui \
    forms/parameters.ui

RESOURCES += \
    ressources/texture.qrc
