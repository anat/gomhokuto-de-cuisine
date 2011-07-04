#-------------------------------------------------
#
# Project created by QtCreator 2011-05-12T22:22:53
#
#-------------------------------------------------

QT       += core gui

TARGET = Gomoku
TEMPLATE = app

INCLUDEPATH += ./inc

SOURCES += \
    src/main.cpp\
    src/APlayer.cpp\
    src/Board.cpp\
    src/Game.cpp\
    src/HPlayer.cpp\
    src/mainwindow.cpp\
    src/Referee.cpp\
    src/Square.cpp \
    src/gridmanager.cpp \
    src/parameters.cpp \
    src/newgame.cpp \
    src/finalstate.cpp \
    src/open.cpp \
    src/BasicHeuristic.cpp \
    src/RefereeManager.cpp \
    src/BasicSearchCase.cpp \
    src/ThreeAlignChecker.cpp

HEADERS  += \
    inc/mainwindow.hpp \
    inc/Types.hpp \
    inc/Square.hpp \
    inc/Referee.hpp \
    inc/HPlayer.hpp \
    inc/gridmanager.hpp \
    inc/Game.hpp \
    inc/Board.hpp \
    inc/APlayer.hpp \
    inc/parameters.hpp \
    inc/newgame.hpp \
    inc/finalstate.hpp \
    inc/open.hpp \
    inc/PlayerAi.hpp \
    inc/IHeuristic.hpp \
    inc/BasicHeuristic.hpp \
    inc/Singleton.hpp \
    inc/RefereeManager.hpp \
    inc/Coord.hpp \
    inc/Array.hpp \
    inc/ISearchCase.hpp \
    inc/BasicSearchCase.hpp \
    inc/ThreeAlignChecker.hpp

FORMS    += \
    forms/mainwindow.ui \
    forms/parameters.ui \
    forms/newgame.ui \
    forms/finalstate.ui \
    forms/open.ui

RESOURCES += \
    ressources/texture.qrc
