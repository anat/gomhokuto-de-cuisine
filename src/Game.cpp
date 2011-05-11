/* 
 * File:   Game.cpp
 * Author: cedric.creusot
 * 
 * Created on May 7, 2011, 10:44 AM
 */

#include <iostream>
#include "Game.hpp"
#include "HPlayer.hpp"

Game::Game(bool vs_computer) : _players(2), _gameboard(), _referee(_gameboard){
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
    Square::Player winner = Square::NOPLAYER;
    while (stillRunning)
    {
        
        getCurrentPlayer()->doAction(_gameboard, _referee);
        _playerTurn = (_playerTurn == Game::TURNPLAYER1) ? (Game::TURNPLAYER2) :
            (TURNPLAYER1);
        if ((winner = _referee->checkWin()) != Square::NOPLAYER)
            stillRunning = false;
    }
    std::cout << "Player : " << winner << " win the game !!!" << std::endl;
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