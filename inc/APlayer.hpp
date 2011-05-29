/* 
 * File:   APlayer.h
 * Author: cedric.creusot
 *
 * Created on May 8, 2011, 11:32 AM
 */

#ifndef APLAYER_H
#define	APLAYER_H


#include "Board.hpp"
#include "Referee.hpp"

class APlayer
{
public :
    APlayer(unsigned int player);
    virtual ~APlayer();
    
    int getNBPawnTaken() const;
    unsigned int getPlayerNum();
    void addPawnTaken(int nb);
    virtual bool doAction(Board & gameboard, Referee & referee, int x = -1, int y = -1) = 0;

private:
    int _nbPawnTaken;
    unsigned int _player;
};

#endif	/* APLAYER_H */

