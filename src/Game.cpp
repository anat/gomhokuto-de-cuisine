/* 
 * File:   Game.cpp
 * Author: cedric.creusot
 * 
 * Created on May 7, 2011, 10:44 AM
 */

#include <iostream>
#include "Game.hpp"
#include "HPlayer.hpp"

Game::Game(bool vs_computer) : _players(2) {
    
    _gameboard = new Board();
    _referee = new Referee(*_gameboard);
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
    std::cout << "Test" << std::endl;
    bool stillRunning = true;
    while (stillRunning)
    {
        //if (_referee.)
        getCurrentPlayer()->doAction(*_gameboard, *_referee);
        _playerTurn = (_playerTurn == Game::TURNPLAYER1) ? (Game::TURNPLAYER2) :
            (TURNPLAYER1);
    }
}

void Game::newGame(bool vs_computer)
{
    delete _gameboard;
    delete _referee;
    delete _players[0];
    delete _players[1];
    _gameboard = new Board();
    _referee = new Referee(*_gameboard);
    _players[TURNPLAYER1] = new HPlayer(Square::PLAYER1);
    _players[TURNPLAYER2] = new HPlayer(Square::PLAYER2);
}