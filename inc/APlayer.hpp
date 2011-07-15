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
    
    unsigned int getPlayerNum();
    virtual bool doAction(Board & gameboard, Referee & referee, int x = -1, int y = -1) = 0;

protected:
    unsigned int _player;
};

#endif	/* APLAYER_H */

