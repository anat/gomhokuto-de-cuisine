/* 
 * File:   Game.cpp
 * Author: cedric.creusot
 * 
 * Created on May 7, 2011, 10:44 AM
 */

#include <iostream>
#include "Game.hpp"
#include "HPlayer.hpp"

Game::Game(bool) 
        : _players(2), _gameboard(), _referee(_gameboard), 
          _playerTurn(PLAYER1)
{
    _players[PLAYER1 - 1] = new HPlayer(PLAYER1);
    _players[PLAYER2 - 1] = new HPlayer(PLAYER2);
}

Game::~Game() {
}

unsigned int Game::getPlayerTurn()
{
    return (_playerTurn);
}

APlayer * Game::getCurrentPlayer()
{
    int i = (int)_playerTurn;
    return (_players[i - 1]);
}

bool Game::doGameGui(int x, int y)
{
    bool mWinner = false;
    bool doActionIsOk = getCurrentPlayer()->doAction(_gameboard, _referee, x, y);
    if (!(mWinner = checkWin()) && doActionIsOk)
        _playerTurn = (_playerTurn == PLAYER1) ? (PLAYER2) :
            (PLAYER1);
    emit clear();
    if (mWinner)
    {
        std::cout << "Gagnant ? " << mWinner << std::endl;
        std::cout << "Who ? " << _playerTurn << std::endl;
        emit winner(_playerTurn);
    }
    _gameboard.DumpBoard();
    return (mWinner);
}


void Game::doGameTerminal()
{
    bool stillRunning = true;
    while (stillRunning)
    {
        getCurrentPlayer()->doAction(_gameboard, _referee);
        stillRunning = !checkWin();
        if (!stillRunning)
            break;
        _playerTurn = (_playerTurn == PLAYER1) ? (PLAYER2) :
            (PLAYER1);
    }
    std::cout << "Player : " << getCurrentPlayer()->getPlayerNum() << " win the game !!!" << std::endl;
}

void Game::newGame(bool)
{
    delete _players[0];
    delete _players[1];
    _referee.reset();
    _gameboard.reset();
    _players[PLAYER1 - 1] = new HPlayer(PLAYER1);
    _players[PLAYER2 - 1] = new HPlayer(PLAYER2);
}

bool Game::checkWin()
{
    if (_referee.checkWin() != NOPLAYER)
        return true;
    if (getCurrentPlayer()->getNBPawnTaken() >= 5)
        return true;
    return false;
}

Board &    Game::getGameBoard()
{
    return (_gameboard);
}

bool    Game::getFivePrize()
{
    return (_referee.fivePrize());
}

bool    Game::getDoubleThree()
{
    return (_referee.doubleThree());
}

void    Game::setFivePrize(bool value)
{
    _referee.fivePrize(value);
}

void    Game::setDoubleThree(bool value)
{
    _referee.doubleThree(value);
}
