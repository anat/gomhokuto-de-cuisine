/* 
 * File:   Referee.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 1:14 PM
 */

#ifndef REFEREE_HPP
#define	REFEREE_HPP

#include "Board.hpp"

/*
 * L'arbitre 
 */

class Referee {
public:
    Referee(Board& board);
    Referee(const Referee& orig);
    virtual ~Referee();

    bool tryPlaceRock(unsigned int x, unsigned int y, Square& square); //Test et si ok place
    bool testPosition(unsigned int x, unsigned int y, Square& square); //Test tout cours
    
private:
    Board& _board;
};

#endif	/* REFEREE_HPP */

