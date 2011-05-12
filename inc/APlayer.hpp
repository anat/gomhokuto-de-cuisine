/* 
 * File:   APlayer.h
 * Author: cedric.creusot
 *
 * Created on May 8, 2011, 11:32 AM
 */

#ifndef APLAYER_H
#define	APLAYER_H

#include "Referee.hpp"
#include "Square.hpp"


class APlayer
{
    int _nbPawnTaken;
    Square::Player _player;
public :
    APlayer(Square::Player player);
    virtual ~APlayer();
    
    int const getNBPawnTaken() const;
    Square::Player & getPlayerNum();
    void addPawnTaken(int nb);
    virtual void doAction(Board & gameboard, Referee & referee) = 0;
};

#endif	/* APLAYER_H */

