/* 
 * File:   Game.cpp
 * Author: cedric.creusot
 * 
 * Created on May 7, 2011, 10:44 AM
 */

#include "Game.h"
#include "HPlayer.h"

Game::Game(bool vs_computer) : 
_gameboard(), _referee(_gameboard), _players(NB_MAX_PLAYER) {

    if (vs_computer)
        ;// TODO : Implémenter l'IA pour plus tard
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
    
}
