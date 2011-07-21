/* 
 * File:   Board.cpp
 * Author: fancel
 * 
 * Created on May 5, 2011, 10:22 AM
 */

#include <iostream>
#include "Board.hpp"
#include "Game.hpp"


Board::Board() : _tab()
{ }

Board::Board(const Board& orig) : _tab(orig._tab)
{ }

Board::~Board()
{ }

Board& Board::operator =(const Board& orig) {
    if (this != &orig) {
        _tab = orig._tab;
    }
    return *this;
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
    return _tab.size();
}

void Board::DumpBoard() const
{
  unsigned int i, j;
  char c;

  std::cout << "   0  1  2  3  4  5  6  7  8  9"
	    << "  10 11 12 13 14 15 16 17 18" << std::endl;
  for (i = 0; i < _tab.size(); ++i) /* Y */
  {
      std::cout.width(2);
      std::cout << i;
      for (j = 0; j < _tab.size(); j++) /* X */
	{
            switch (_tab[i][j].getPlayer())
	    {
                case NOPLAYER   : c = '.'; break;
                case PLAYER1    : c = 'X'; break;
                case PLAYER2    : c = 'O'; break;
                default         : c = '?'; break;
	    }
	  std::cout << " ";
	  std::cout << c;
	  std::cout << " ";
	}
      std::cout << std::endl;
  }
  std::cout.flush();

//  for (unsigned int y = 0; y < _tab.size(); ++y) {
//      for (unsigned int x = 0; x < _tab.size(); ++x) {
//          if (_tab[y][x].getPlayer()) {
//              std::cout << "x " << x << " y " << y << std::endl;
//              _tab[y][x].dumpData();
//          }
//      }
//  }
  std::cout.flush();
}
  
void Board::reset()
{
    for (unsigned int i = 0; i < _tab.size(); ++i)
        for (unsigned int o = 0; o < _tab[i].size(); ++o)
            _tab[i][o].setRawData(0);
}
