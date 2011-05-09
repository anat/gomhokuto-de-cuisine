/* 
 * File:   Referee.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 1:14 PM
 */

#ifndef REFEREE_HPP
#define	REFEREE_HPP

#include "Board.hpp"

#define DIR_UP    0x1
#define DIR_DOWN  0x2
#define DIR_LEFT  0x4
#define DIR_RIGHT 0x8

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
        void propagation(unsigned int x, unsigned int y, const Square::Player& player,
                         unsigned int dir, unsigned int usize);
	void propagation_inverse(unsigned int x, unsigned int y, const Square::Player& player);
        int lineSize(unsigned int x, unsigned int y, const Square::Player& player, int dir);
	void checkPrise(unsigned int x, unsigned int y, const Square::Player& player);
private:
    Board& _board;
};

#endif	/* REFEREE_HPP */

