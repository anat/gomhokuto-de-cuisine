/* 
 * File:   Board.cpp
 * Author: fancel
 * 
 * Created on May 5, 2011, 10:22 AM
 */


#include "Board.hpp"

Board::Board(std::size_t size) : _tab(), _size(size) {
	_tab.resize(size, std::vector<Square>(size));
}

Board::Board(const Board& orig) : _tab(orig._tab), _size(orig._size) {
}

Board::~Board() {
}

const Square& Board::getCase(unsigned int x, unsigned int y) const {
    if (checkSize(x, y))
        return _tab[y][x];
    throw BoardException();
}

Square& Board::getCase(unsigned int x, unsigned int y) {
    if (checkSize(x, y))
        return _tab[y][x];
    throw BoardException();
}

const Square& Board::operator()(unsigned int x, unsigned int y) const {
    if (checkSize(x, y))
        return _tab[y][x];
    throw BoardException();
}

Square& Board::operator()(unsigned int x, unsigned int y) {
    if (checkSize(x, y))
        return _tab[y][x];
    throw BoardException();
}

void Board::setCase(unsigned int x, unsigned int y, const Square& value) {
    if (checkSize(x, y))
        _tab[y][x] = value;
}

std::size_t Board::getSize() const {
    return _size;
}

bool Board::checkSize(unsigned int x, unsigned int y) const {
    return ((x < _size) && (y < _size));
}

