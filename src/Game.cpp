/* 
 * File:   Game.cpp
 * Author: cedric.creusot
 * 
 * Created on May 7, 2011, 10:44 AM
 */

#include "Game.h"

Game::Game(bool vs_computer) : _gameboard(), _referee(_gameboard) {

    if (vs_computer)
        ;// TODO : Implémenter l'IA pour plus tard
    //_players[TURNPLAYER1] = new APlayer();
    //_players[TURNPLAYER2] = new APlayer();
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
