/* 
 * File:   Game.h
 * Author: cedric.creusot
 *
 * Created on May 7, 2011, 10:44 AM
 */

#ifndef GAME_H
#define	GAME_H

#include <vector>
#include "Referee.hpp"
#include "Board.hpp"
#include "APlayer.h"

#define NB_MAX_PLAYER 2

class Game {
public:
    enum PlayerTurn
    {
        TURNPLAYER1,
        TURNPLAYER2
    };
    
    Game(bool vs_computer = false);
    virtual ~Game();
    
    PlayerTurn getPlayerTurn();
    APlayer *  getCurrentPlayer();
    void       doGame();

private:
    Board       _gameboard;
    Referee     _referee;
    std::vector<APlayer*>   _players;
    PlayerTurn  _playerTurn;    
};

#endif	/* GAME_H */

