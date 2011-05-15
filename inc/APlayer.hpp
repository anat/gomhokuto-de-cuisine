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
public :
    APlayer(Square::Player player);
    virtual ~APlayer();
    
    int getNBPawnTaken() const;
    Square::Player & getPlayerNum();
    void addPawnTaken(int nb);
    virtual void doAction(Board & gameboard, Referee & referee) = 0;

private:
    int _nbPawnTaken;
    Square::Player _player;
};

#endif	/* APLAYER_H */

