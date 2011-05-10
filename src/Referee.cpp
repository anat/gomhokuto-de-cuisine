/* 
 * File:   Referee.cpp
 * Author: fancel
 * 
 * Created on May 5, 2011, 1:14 PM
 */

#include "Referee.hpp"
#include <iostream>

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
  if (0)
    {
      //propagation_inverse(?, ?, (player == Square::PLAYER1) ? Square::PLAYER2 : Square::PLAYER1);
      //propagation_inverse(?, ?, (player == Square::PLAYER1) ? Square::PLAYER2 : Square::PLAYER1);
    }
}

bool Referee::checkPosition(unsigned int x, unsigned int y)
{
	return (x < _board.getSize() && y < _board.getSize());
}

/* Try to propagate in EVERY directions */
void Referee::propagation(unsigned int x, unsigned int y, const Square::Player& player)
{
  int usize; /* Updated size of (horizontal/vertical/diagonal) line */

  //std::cout << " ORG " << x << " " << y << std::endl;
  usize = _board(x, y)._vert = _board(x, y-1)._vert + _board(x, y+1)._vert + 1;
  propagation(x, y, player, DIR_UP               , usize);
  propagation(x, y, player, DIR_DOWN             , usize);

  usize = _board(x, y)._horz = _board(x-1, y)._horz + _board(x+1, y)._horz + 1;
  propagation(x, y, player, DIR_LEFT             , usize);
  propagation(x, y, player, DIR_RIGHT            , usize);

  usize = _board(x, y)._diagl = _board(x-1, y-1)._diagl + _board(x+1, y+1)._diagl + 1;
  propagation(x, y, player, DIR_UP   | DIR_LEFT  , usize);
  propagation(x, y, player, DIR_DOWN | DIR_RIGHT , usize);

  usize = _board(x, y)._diagr = _board(x+1, y-1)._diagr + _board(x-1, y+1)._diagr + 1;
  propagation(x, y, player, DIR_UP   | DIR_RIGHT , usize);
  propagation(x, y, player, DIR_DOWN | DIR_LEFT  , usize);
}

/* Try to propagate in ONE direction */
void Referee::propagation(unsigned int x, unsigned int y, const Square::Player& player,
			  unsigned int dir, unsigned int usize)
{
  int i = 0x8;

  do
    switch(dir & i)
      {
      case DIR_UP:    y--; break;
      case DIR_DOWN:  y++; break;
      case DIR_LEFT:  x--; break;
      case DIR_RIGHT: x++; break;
      default:             break;
      }
  while ((i >>= 1));

  if (_board(x, y).getPlayer() == player)
    {
      //std::cout << "  IN " << x << " " << y << "  usize(" << usize << ")" << std::endl;
      switch(dir)
	{
	case DIR_UP:               _board(x, y)._vert  = usize; break;
	case DIR_DOWN:             _board(x, y)._vert  = usize; break;
	case DIR_LEFT:             _board(x, y)._horz  = usize; break;
	case DIR_RIGHT:            _board(x, y)._horz  = usize; break;
	case DIR_UP   | DIR_LEFT:  _board(x, y)._diagl = usize; break;
	case DIR_DOWN | DIR_RIGHT: _board(x, y)._diagl = usize; break;
	case DIR_UP   | DIR_RIGHT: _board(x, y)._diagr = usize; break;
	case DIR_DOWN | DIR_LEFT:  _board(x, y)._diagr = usize; break;
	default:                    break;
	}
      propagation(x, y, player, dir, usize);
    }
}

void Referee::propagation_inverse(unsigned int x, unsigned int y, const Square::Player& player)
{
  int usize1;
  int usize2;

  //std::cout << " ORG " << x << " " << y << "    <- INVERSE" << std::endl;
  usize1 = lineSize(x, y, player, DIR_UP);
  usize2 = _board(x, y)._vert - usize1 - 1;
  propagation(x, y, player, DIR_UP               , usize1);
  propagation(x, y, player, DIR_DOWN             , usize2);

  usize1 = lineSize(x, y, player, DIR_LEFT);
  usize2 = _board(x, y)._horz - usize1 - 1;
  propagation(x, y, player, DIR_LEFT             , usize1);
  propagation(x, y, player, DIR_RIGHT            , usize2);

  usize1 = lineSize(x, y, player, DIR_UP | DIR_LEFT);
  usize2 = _board(x, y)._diagl - usize1 - 1;
  propagation(x, y, player, DIR_UP   | DIR_LEFT  , usize1);
  propagation(x, y, player, DIR_DOWN | DIR_RIGHT , usize2);

  usize1 = lineSize(x, y, player, DIR_UP | DIR_RIGHT);
  usize2 = _board(x, y)._diagr - usize1 - 1;
  propagation(x, y, player, DIR_UP   | DIR_RIGHT , usize1);
  propagation(x, y, player, DIR_DOWN | DIR_LEFT  , usize2);  

  _board(x, y)._horz  = 0;
  _board(x, y)._vert  = 0;
  _board(x, y)._diagl = 0;
  _board(x, y)._diagr = 0;
  _board(x, y).setPlayer(Square::NOPLAYER);
}

int Referee::lineSize(unsigned int x, unsigned int y, const Square::Player& player, int dir)
{
  int i = 0x8;

  do
    switch(dir & i)
      {
      case DIR_UP:    y--; break;
      case DIR_DOWN:  y++; break;
      case DIR_LEFT:  x--; break;
      case DIR_RIGHT: x++; break;
      default:             break;
      }
  while ((i >>= 1));

  if (_board(x, y).getPlayer() == player)
    return lineSize(x, y, player, dir) + 1;
  return 0;
}
