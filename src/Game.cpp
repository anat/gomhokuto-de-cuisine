/* 
 * File:   Game.cpp
 * Author: cedric.creusot
 * 
 * Created on May 7, 2011, 10:44 AM
 */

#include <iostream>
#include "Game.hpp"
#include "HPlayer.hpp"

Game::Game(bool vs_computer) 
        : _players(2), _gameboard(), _referee(_gameboard), 
          _playerTurn(TURNPLAYER1)
{
    _players[TURNPLAYER1] = new HPlayer(Square::PLAYER1);
    _players[TURNPLAYER2] = new HPlayer(Square::PLAYER2);
}

Game::~Game() {
}

Game::PlayerTurn Game::getPlayerTurn()
{
    return (_playerTurn);
}

APlayer * Game::getCurrentPlayer()
{
    int i = (int)_playerTurn;
    return (_players[i]);
}

void Game::doGame()
{
    bool stillRunning = true;
    while (stillRunning)
    {
        getCurrentPlayer()->doAction(_gameboard, _referee);
        stillRunning = !checkWin();
        if (!stillRunning)
            break;
        _playerTurn = (_playerTurn == Game::TURNPLAYER1) ? (Game::TURNPLAYER2) :
            (TURNPLAYER1);
    }
    std::cout << "Player : " << getCurrentPlayer()->getPlayerNum() << " win the game !!!" << std::endl;
}

void Game::newGame(bool vs_computer)
{
    delete _players[0];
    delete _players[1];
    _referee.reset();
    _gameboard.reset();
    _players[TURNPLAYER1] = new HPlayer(Square::PLAYER1);
    _players[TURNPLAYER2] = new HPlayer(Square::PLAYER2);
}

bool Game::checkWin()
{
    if (_referee.checkWin() != Square::NOPLAYER)
        return true;
    if (getCurrentPlayer()->getNBPawnTaken() >= 5)
        return true;
    return false;
}

Board &    Game::getGameBoard()
{
    return (_gameboard);
}