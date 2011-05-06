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

	int tryPlaceRock(unsigned int x, unsigned int y, Square::Player& square); //Test et si ok place
    bool testPosition(unsigned int x, unsigned int y); //Test tout cours
	void checkAlignement(unsigned int x, unsigned int y);
	bool checkPosition(unsigned int x, unsigned int y);
	void propagation(unsigned int x, unsigned int y, const Square::Player& player);
	void propagation_inverse(unsigned int x, unsigned int y);
	void checkPrise(unsigned int x, unsigned int y, const Square::Player& player);
private:
    Board& _board;
};

#endif	/* REFEREE_HPP */

