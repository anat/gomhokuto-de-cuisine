/* 
 * File:   APlayer.h
 * Author: cedric.creusot
 *
 * Created on May 8, 2011, 11:32 AM
 */

#ifndef APLAYER_H
#define	APLAYER_H

#include "Referee.hpp"

class APlayer
{
    int _nbPawnTaken;

public :
    APlayer();
    virtual ~APlayer();
    
    int const getNBPawnTaken() const;
    void incrementPawnTaken();
    virtual void doAction(Board & gameboard, Referee & referee) = 0;
};

#endif	/* APLAYER_H */

