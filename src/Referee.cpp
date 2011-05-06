/* 
 * File:   Referee.cpp
 * Author: fancel
 * 
 * Created on May 5, 2011, 1:14 PM
 */

#include "Referee.hpp"

Referee::Referee(Board& board) : _board(board) {
}

Referee::Referee(const Referee& orig)  : _board(orig._board) {
}

Referee::~Referee() {
}

int Referee::tryPlaceRock(unsigned int x, unsigned int y, Square::Player& player) {
    int value = -1;

    if (testPosition(x, y)) {
		_board(x, y).setPlayer(player);
		checkPrise(x, y, player);
		propagation(x, y, player);
        value = 0;
    }
    return value;
}

bool Referee::testPosition(unsigned int x, unsigned int y) {
    bool value = false;

	if (checkPosition(x, y) && _board(x, y).getPlayer() == Square::NOPLAYER) { //rajouter les tests de pattern ici
        value = true;
    }
    return value;
}

void Referee::checkAlignement(unsigned int x, unsigned int y)
{
	
}

void Referee::checkPrise(unsigned int x, unsigned int y, const Square::Player& player)
{

}

bool Referee::checkPosition(unsigned int x, unsigned int y)
{
	return (x < _board.getSize() && y < _board.getSize());
}

void Referee::propagation(unsigned int x, unsigned int y, const Square::Player& player)
{
}

void Referee::propagation_inverse(unsigned int x, unsigned int y)
{

}