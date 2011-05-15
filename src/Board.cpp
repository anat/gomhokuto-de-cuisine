/* 
 * File:   Board.cpp
 * Author: fancel
 * 
 * Created on May 5, 2011, 10:22 AM
 */

#include <iostream>
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

void Board::DumpBoard()
{
	/*
  unsigned int i, j;
  char c;

  std::cout << "   0  1  2  3  4  5  6  7  8  9"
	    << "  10 11 12 13 14 15 16 17 18" << std::endl;
  for (i = 0; i < _size; i++) /* Y */
	/*
    {
      std::cout.width(2);
      std::cout << i;
      for (j = 0; j < _size; j++) /* X */
	/*
	{
	  switch (_tab[i][j].getPlayer())
	    {
	    case Square::NOPLAYER: c = '.'; break;
	    case Square::PLAYER1:  c = 'X'; break;
	    case Square::PLAYER2:  c = 'O'; break;
	    default:               c = '?'; break;
	    }
	  std::cout << " ";
	  std::cout << c;
	  std::cout << " ";
	}
      std::cout << std::endl;
    }
	*/
}
  
void Board::reset()
{
    for (unsigned int i = 0; i < _size; ++i)
        _tab[i].clear();
    _tab.clear();
    _tab.resize(_size, std::vector<Square>(_size));
}