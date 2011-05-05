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

bool Referee::tryPlaceRock(unsigned int x, unsigned int y, Square& square) {
    bool value = false;

    if (testPosition(x, y, square)) {
        _board.setCase(x, y, square);
        value = true;
    }
    return value;
}

bool Referee::testPosition(unsigned int x, unsigned int y, Square& ) {
    bool value = false;

    if (_board(x, y)._status == Square::NOP) { //rajouter les tests de pattern ici
        value = true;
    }
    return value;
}