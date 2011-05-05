/* 
 * File:   Square.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 12:19 PM
 */

#ifndef SQUARE_HPP
#define	SQUARE_HPP

struct Square {
    enum Statue {
        NOP,
        PLAYER1,
        PLAYER2
    };

    Statue _status;

    Square();
};

#endif	/* SQUARE_HPP */

