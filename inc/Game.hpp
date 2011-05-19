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
#include "APlayer.hpp"

#define NOPLAYER 0
#define PLAYER1 1
#define PLAYER2 2
#define NB_MAX_PLAYER 2

class Game {
public:    
    Game(bool vs_computer = false);
    virtual ~Game();
    
    unsigned int     getPlayerTurn();
    APlayer *  getCurrentPlayer();
    bool       doGameGui(int x, int y);
    void       doGameTerminal();
    void       newGame(bool vs_computer = false);
    bool       checkWin();
    Board &    getGameBoard();
    bool       getDoubleThree();
    bool       getFivePrize();
    void       setDoubleThree(bool value);
    void       setFivePrize(bool value);
    
private:
    std::vector<APlayer*>   _players;
    Board                   _gameboard;
    Referee                 _referee;
    unsigned int            _playerTurn;
};

#endif	/* GAME_H */

