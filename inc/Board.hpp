/* 
 * File:   Board.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 10:22 AM
 */

#ifndef BOARD_HPP
#define	BOARD_HPP

#include <vector>

#include "Square.hpp"

class BoardException : public std::exception {
    const char* what() const throw (){
        return "tu sort du tableau connard !!!11";
    }
};

class Board {
public:
    typedef std::vector< std::vector< Square > > SquareTab;

    Board(std::size_t size = 19);
    Board(const Board& orig);
    ~Board();

    const Square& getCase(unsigned int x = 0, unsigned int y = 0) const;
    Square& getCase(unsigned int x = 0, unsigned int y = 0);
    const Square& operator()(unsigned int x = 0, unsigned int y = 0) const;
    Square& operator()(unsigned int x = 0, unsigned int y = 0);
    void setCase(unsigned int x, unsigned int y, const Square& value);
    std::size_t getSize() const;
    void DumpBoard();
    void reset();

private:
    SquareTab _tab;
    std::size_t _size;

    bool checkSize(unsigned int x, unsigned int y) const;
};

#endif	/* BOARD_HPP */

