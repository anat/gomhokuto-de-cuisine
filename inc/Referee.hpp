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
	bool testPosition(unsigned int x, unsigned int y, Square::Player& player); //Test tout cours
	const Square::Player& checkWin() const;
	void propagation_inverse(unsigned int x, unsigned int y, const Square::Player& player);
	bool doubleThree() const;
	bool fivePrize() const;
	bool doubleThree(bool value);
	bool fivePrize(bool value);
	void reset();

private:
	bool _fivePrize;
	bool _doubleThree;
	Square::Player _winner;
	Board& _board;

	inline Square::Player opponant(const Square::Player& pla) {
		Square::Player result = Square::NOPLAYER;
		if (pla == Square::PLAYER1)
			result = Square::PLAYER2;
		else if (pla == Square::PLAYER2)
			result = Square::PLAYER1;
		return result;
	}

	inline bool checkPosition(unsigned int x, unsigned int y) {
		return (x < _board.getSize() && y < _board.getSize());
	}

	inline unsigned int abs(int value) {
		if (value < 0)
			return value * -1;
		return value;
	}

	bool checkDoubleThree(unsigned int x, unsigned int y, Square::Player& player);
	bool checkFivePrize(unsigned int x, unsigned int y, Square::Player& player);
	bool Link3OrMore(unsigned int x, unsigned int y, const Square::Player& player);
	bool EndLink2OrMore(unsigned int x, unsigned int y, const Square::Player& player);
	bool checkNearBlock(unsigned int xorig, unsigned int yorig, unsigned int x, unsigned int y, const Square::Player& player);
	void checkWin(unsigned int x, unsigned int y, Square::Player& player);
	unsigned int checkPrize(unsigned int x, unsigned int y, const Square::Player& player);
	bool checkPrize(unsigned int x, unsigned int y, int xvec, int yvec, const Square::Player& play);
	void cleanRock(unsigned int x, unsigned int y, int xvec, int yvec, const Square::Player& play);
	void propagation(unsigned int x, unsigned int y, const Square::Player& player);
	void propagation(unsigned int x, unsigned int y, const Square::Player& player,
		unsigned int dir, unsigned int usize);
	
	int lineSize(unsigned int x, unsigned int y, const Square::Player& player, int dir);
};

#endif	/* REFEREE_HPP */

