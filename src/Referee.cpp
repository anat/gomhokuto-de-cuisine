/* 
* File:   Referee.cpp
* Author: fancel
* 
* Created on May 5, 2011, 1:14 PM
*/

#include "Referee.hpp"
#include <iostream>

Referee::Referee(Board& board) 
	: _board(board), _winner(0), _fivePrize(false), _doubleThree(false), _directionIncrement() {
		InitDirection();
}

Referee::Referee(const Referee& orig)  
	: _board(orig._board), _winner(orig._winner), _fivePrize(orig._fivePrize), _doubleThree(orig._doubleThree), _directionIncrement(orig._directionIncrement) {
}

Referee::~Referee() {
}

void Referee::InitDirection() {
	_directionIncrement.push_back(Coord(1, 0));
	_directionIncrement.push_back(Coord(1, -1));
	_directionIncrement.push_back(Coord(0, -1));
	_directionIncrement.push_back(Coord(-1, -1));
	_directionIncrement.push_back(Coord(-1, 0));
	_directionIncrement.push_back(Coord(-1, 1));
	_directionIncrement.push_back(Coord(0, 1));
	_directionIncrement.push_back(Coord(1, 1));
}

/**
* deplace x et y dans la direction choisie
*/
bool Referee::goTo(unsigned int& x, unsigned int& y, Vector dir) {
	if (checkPosition(x + _directionIncrement[dir].x, y + _directionIncrement[dir].y)) {
		x += _directionIncrement[dir].x;
		y += _directionIncrement[dir].y;

		return true;
	}
	return false;
}

/**
* Recupere la valeur de l'alignement dans la direction choisie
*/
unsigned int Referee::getDirAlign(const Square& value, Vector dir){
	if (dir == RIGHT || dir == LEFT)
		return GET_HORZ(value.getRawData());
	if (dir == UP || dir == DOWN)
		return GET_VERT(value.getRawData());
	if (dir == UP_LEFT || dir == DOWN_RIGHT)
		return GET_DIAGL(value.getRawData());
	if (dir == UP_RIGHT || dir == DOWN_LEFT)
		return GET_DIAGR(value.getRawData());
	return 0;
}

/*
* Teste si la case fait partie d'au moins un alignement de 'size'
*/
bool Referee::ispartOfAlign(const Square& value, int size) {
	return (
		GET_DIAGL(value.getRawData()) >= size ||
		GET_DIAGR(value.getRawData()) >= size || 
		GET_HORZ(value.getRawData()) >= size || 
		GET_VERT(value.getRawData()) >= size
		);
}

/**
* get de l'atribut qui contient le gagnant
*/
unsigned int Referee::checkWin() const {
	return _winner;
}

/**
* reset le gagnant
*/
void Referee::reset() {
	_winner = 0;
}

/**
* Tente de placer une pierre
*/
int Referee::tryPlaceRock(unsigned int x, unsigned int y, unsigned int player) {
	int value = -1;

	if (testPosition(x, y, player)) {
		_board(x, y).setRawData(_board(x, y).getRawData() | PLAYER(player));
		propagation(x, y, player);
		value = checkPrize(x, y, player);
		checkWin(x, y, player);
	}
	return value;
}

/**
* Determine si la position est valide pour une nouvelle pierre
*/
bool Referee::testPosition(unsigned int x, unsigned int y, unsigned int player) {
	bool value = false;

	if (checkPosition(x, y) && GET_PLAYER(_board(x, y).getRawData()) == 0) { //rajouter les tests de pattern ici

		value = true;
		if (_doubleThree)
			value = checkDoubleThree(x, y, player);
	}
	return value;
}

/**
* cherche dans toute les directions si il a des pierre a prendre
*/
unsigned int Referee::checkPrize(unsigned int x, unsigned int y, unsigned int player)
{
	unsigned int result = 0;

	for (std::size_t i = 0; i < _directionIncrement.size(); ++i) {
		if (checkPrize(x, y, static_cast<Vector>(i), player)) {
			cleanRock(x, y, static_cast<Vector>(i), player);
			result++;
		}
	}
	return result;
}

/**
* cherche si il y a une prise dans une direction
*/
bool Referee::checkPrize(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
	unsigned int i = 0;
	if (checkIsTakable(x, y, dir, player)) 
	{
		goTo(x, y, dir);
		_board(x, y).setRawData(_board(x, y).getRawData() | IS_TAKABLE(1));
		goTo(x, y, dir);
		_board(x, y).setRawData(_board(x, y).getRawData() | IS_TAKABLE(1));
		if (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player)
			return true;
	}
	return false;
}

/**
* check si les pions dans la direction sont prenable par le joueurs player
*/ 

bool Referee::checkIsTakable(unsigned x, unsigned int y, Vector dir, unsigned int player) {
	return (goTo(x, y, dir) && 
		GET_PLAYER(_board(x, y).getRawData()) == opponant(player) && 
		getDirAlign(_board(x, y), dir) == 2 && goTo(x, y, dir) && goTo(x, y, dir));
}

/**
* clean les pierre trouver comme prise
*/
void Referee::cleanRock(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
	goTo(x, y, dir);
	_board(x, y).setRawData(_board(x, y).getRawData() | PLAYER(0));
	propagation_inverse(x, y, opponant(player));

	goTo(x, y, dir);
	_board(x, y).setRawData(_board(x, y).getRawData() | PLAYER(0));
	propagation_inverse(x, y, opponant(player));
}


/**
* Determine si le coup est gagnant
*/
void Referee::checkWin(unsigned int x, unsigned int y, unsigned int player)
{
	if (ispartOfAlign(_board(x, y), 5)) {
		if (_fivePrize) {
			if (checkFivePrize(x, y, player))
				_winner = player;
		} else {
			_winner = player;
		}
	}
}


/**
* Fonction de test de la regle speciale des 5 pions lors d'une tentative de victoire
*/
bool Referee::checkFivePrize(unsigned int x, unsigned int y, unsigned int player) {
	if (GET_DIAGL(_board(x, y).getRawData()) > 4) {
		unsigned int size = checkFivePrize(x, y, UP_LEFT , player);
		size += checkFivePrize(x, y, DOWN_RIGHT, player);
		if (size > 4)
			return true;
	}

	if (GET_DIAGR(_board(x, y).getRawData()) > 4) {
		unsigned int size = checkFivePrize(x, y, UP_RIGHT, player);
		size += checkFivePrize(x, y, DOWN_LEFT, player);
		if (size > 4)
			return true;
	}

	if (GET_HORZ(_board(x, y).getRawData()) > 4) {
		unsigned int size = checkFivePrize(x, y, RIGHT, player);
		size += checkFivePrize(x, y, LEFT, player);
		if (size > 4)
			return true;
	}

	if (GET_VERT(_board(x, y).getRawData()) > 4) {
		unsigned int size = checkFivePrize(x, y, UP, player);
		size += checkFivePrize(x, y, DOWN, player);
		if (size > 4)
			return true;
	}

	return false;
}

unsigned int Referee::checkFivePrize(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
	int cleanRock = 0;

	while (goTo(x, y, dir) && (GET_PLAYER(_board(x, y).getRawData()) == player) && (GET_TAKABLE(_board(x, y).getRawData()) == 0)) {
		cleanRock++;
	}
	return cleanRock;
}

/**
* Get/Set pour les regles speciales
*/
bool Referee::doubleThree() const {
	return _doubleThree;
}

bool Referee::doubleThree(bool value) {
	_doubleThree = value;
	return _doubleThree;
}

bool Referee::fivePrize() const {
	return _fivePrize;
}

bool Referee::fivePrize(bool value) {
	_fivePrize = value;
	return _fivePrize;
}

/*
* Fonction de test de la regle speciale des double 3 pions align
*/
bool Referee::checkDoubleThree(unsigned int x, unsigned int y, unsigned int player) {
	unsigned int num = 0;
	for (unsigned int i = 0; i < _directionIncrement.size(); i++) {
		if (isPartOfFree3Align(x, y, static_cast<Vector>(i), player))
			num++;
	}

	if (num > 2)
		return false;
	return true;
}

bool Referee::isPartOfFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
	unsigned int xnear = x;
	unsigned int ynear = y;
	if (goTo(xnear, ynear, invert(dir)) && GET_PLAYER(_board(xnear, ynear).getRawData()) != opponant(player) &&
		(classicFree3Align(x, y, dir, player) || unClassicFree3Align(x, y, dir, player)))
	{
		return true;
	}
	return false;
}

bool Referee::classicFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
	return (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player && 
		goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player && 
		goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) != opponant(player));
}

bool Referee::unClassicFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
	return (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == 0 && 
		goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player && 
		goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player &&
		goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) != opponant(player));
}

/* Try to propagate in EVERY directions */
void Referee::propagation(unsigned int x, unsigned int y, unsigned int player)
{

	int usize; /* Updated size of (horizontal/vertical/diagonal) line */

		/*
	//std::cout << " ORG " << x << " " << y << std::endl;
	if (checkPosition(x, y+1))
	  _board(x, y)._vert  = _board(x, y+1)._vert;
	if (checkPosition(x, y-1))
	  _board(x, y)._vert += _board(x, y-1)._vert;
	usize = _board(x, y)._vert + 1;

	propagation(x, y, player, DIR_UP               , usize);
	propagation(x, y, player, DIR_DOWN             , usize);

	if (checkPosition(x-1, y))
	  _board(x, y)._vert  = _board(x-1, y)._vert;
	if (checkPosition(x+1, y))
	  _board(x, y)._vert += _board(x+1, y)._vert;
	usize = _board(x, y)._horz + 1;

	propagation(x, y, player, DIR_LEFT             , usize);
	propagation(x, y, player, DIR_RIGHT            , usize);

	if (checkPosition(x-1, y-1))
	  _board(x, y)._vert  = _board(x-1, y-1)._vert;
	if (checkPosition(x+1, y+1))
	  _board(x, y)._vert += _board(x+1, y+1)._vert;
	usize = _board(x, y)._diagl + 1;

	propagation(x, y, player, DIR_UP   | DIR_LEFT  , usize);
	propagation(x, y, player, DIR_DOWN | DIR_RIGHT , usize);

	if (checkPosition(x+1, y-1))
	  _board(x, y)._vert  = _board(x+1, y-1)._vert;
	if (checkPosition(x-1, y+1))
	  _board(x, y)._vert += _board(x-1, y+1)._vert;
	usize = _board(x, y)._diagr + 1;

	propagation(x, y, player, DIR_UP   | DIR_RIGHT , usize);
	propagation(x, y, player, DIR_DOWN | DIR_LEFT  , usize);

	/*
	int link[5] = {0};

	if (_board(x, y)._horz == 1  || _board(x, y)._vert == 1 ||
	    _board(x, y)._diagl == 1 || _board(x, y)._diagr == 1)
	  link[0]++;
	link[_board(x, y)._horz  - 1]++;
	link[_board(x, y)._vert  - 1]++;
	link[_board(x, y)._diagl - 1]++;
	link[_board(x, y)._diagr - 1]++;

	updateTruc(x-1, y-1, player, link);
	updateTruc(x-1, y,   player, link);
	updateTruc(x-1, y+1, player, link);
	updateTruc(x,   y-1, player, link);
	updateTruc(x,   y+1, player, link);
	updateTruc(x+1, y-1, player, link);
	updateTruc(x+1, y,   player, link);
	updateTruc(x+1, y+1, player, link);*/
}
/*
void Referee::updateTruc(unsigned int x, unsigned int y, const Square::Player& player, int l[5])
			 //int l1, int l2, int l3, int l4, int l5)
{
  std::cout << "Update : " << l[0]  << l[1]  << l[2]  << l[3]  << l[4] << std::endl;
  _board(x, y).getValues(player)[Square::LINK1] += l[0];
  _board(x, y).getValues(player)[Square::LINK2] += l[1];
  _board(x, y).getValues(player)[Square::LINK3] += l[2];
  _board(x, y).getValues(player)[Square::LINK4] += l[3];
  _board(x, y).getValues(player)[Square::LINK5] += l[4];
  }*/

/* Try to propagate in ONE direction */
void Referee::propagation(unsigned int x, unsigned int y, unsigned int player,
	unsigned int dir, unsigned int usize)
{
	/*
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

	

	if (checkPosition(x, y) && _board(x, y).getPlayer() == player)
	{
		std::cout << "  IN " << x << " " << y << "  usize(" << usize << ")" << std::endl;
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
	*/
}

void Referee::propagation_inverse(unsigned int x, unsigned int y, unsigned int player)
{
	/*
	int usize1;
	int usize2;

	std::cout << " ORG " << x << " " << y << "    <- INVERSE" << std::endl;
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
	*/
}

int Referee::lineSize(unsigned int x, unsigned int y, unsigned int player, int dir)
{
	/*
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

	*/
		return 0;
}
