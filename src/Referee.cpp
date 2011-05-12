/* 
* File:   Referee.cpp
* Author: fancel
* 
* Created on May 5, 2011, 1:14 PM
*/

#include "Referee.hpp"
#include <iostream>

Referee::Referee(Board& board) 
	: _board(board), _winner(Square::NOPLAYER), _fivePrize(false), _doubleThree(false) {
}

Referee::Referee(const Referee& orig)  
	: _board(orig._board), _winner(orig._winner), _fivePrize(orig._fivePrize), _doubleThree(orig._doubleThree) {
}

Referee::~Referee() {
}

/**
* Tente de placer une pierre
*/
int Referee::tryPlaceRock(unsigned int x, unsigned int y, Square::Player& player) {
	int value = -1;

	if (testPosition(x, y, player)) {
		_board(x, y).setPlayer(player);
		value = checkPrize(x, y, player);
		propagation(x, y, player);
		checkWin(x, y, player);
	}
	return value;
}

/**
* Determine si la position est valide pour une nouvelle pierre
*/
bool Referee::testPosition(unsigned int x, unsigned int y, Square::Player& player) {
	bool value = false;

	if (checkPosition(x, y) && _board(x, y).getPlayer() == Square::NOPLAYER) { //rajouter les tests de pattern ici

		value = true;
		if (_doubleThree)
			value = checkDoubleThree(x, y, player);
	}
	return value;
}

/**
* cherche dans toute les directions si il a des pierre a prendre
*/
unsigned int Referee::checkPrize(unsigned int x, unsigned int y, const Square::Player& player)
{
	unsigned int result = 0;
	int xvec = -1;
	int yvec = -1;

	//if (_board(x, y).getValues(opponant(player))[Square::END_LINK2] > 1) {
	for (int xvec = -1; xvec < 2; xvec++) {
		for (int yvec = -1; yvec < 2; yvec++) {
			if ((xvec || yvec) && checkPrize(x, y, xvec, yvec, player)) {
				cleanRock(x, y, xvec, yvec, player);
				result++;
			}
		}
	}
	//	}
	return result;
}

/**
* Determine si le coup est gagnant
*/
void Referee::checkWin(unsigned int x, unsigned int y, Square::Player& player)
{
	if (checkfiveWin(x, y, player)) {
		if (_fivePrize) {
			if (checkFivePrize(x, y, player))
				_winner = player;
		} else {
			_winner = player;
		}
	}
}

bool Referee::checkfiveWin(unsigned int x, unsigned int y, Square::Player& player)
{
	return ((_board(x, y)._diagl > 4) || (_board(x, y)._horz > 4) || (_board(x, y)._vert > 4) || (_board(x ,y)._diagr > 4));
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

/**
* Fonction de test de la regle speciale des 5 pions lors d'une tentative de victoire
*/
bool Referee::checkFivePrize(unsigned int x, unsigned int y, Square::Player& player) {
	if (_board(x, y)._horz > 4) {
		unsigned int size = checkFivePrize(x, y, 1, 0, player);
		size += checkFivePrize(x, y, -1, 0, player);
		if (size > 4)
			return true;
	}
	if (_board(x, y)._vert > 4) {
		unsigned int size = checkFivePrize(x, y, 0, 1, player);
		size += checkFivePrize(x, y, 0, -1, player);
		if (size > 4)
			return true;
	}
	if (_board(x, y)._diagl > 4) {
		unsigned int size = checkFivePrize(x, y, -1, -1, player);
		size += checkFivePrize(x, y, 1, 1, player);
		if (size > 4)
			return true;
	}
	if (_board(x, y)._diagr > 4) {
		unsigned int size = checkFivePrize(x, y, -1, 1, player);
		size += checkFivePrize(x, y, 1, -1, player);
		if (size > 4)
			return true;
	}
	return false;
}

int Referee::checkFivePrize(unsigned int x, unsigned int y, unsigned int xvec, unsigned int yvec, Square::Player& player) {
	int cleanRock = 0;

	x += xvec;
	y += yvec;
	while (checkPosition(x, y) && _board(x, y).getPlayer() == player && !checkNear2Block(x, y, opponant(player))) {
		x += xvec;
		y += yvec;
		cleanRock++;
	}
	return cleanRock;
}

/**
* Test si une pierre appartient au joueurs player et est a <= 2 case de x et y
*/
bool Referee::checkNear2Block(unsigned int x, unsigned int y, const Square::Player& player) {\
	for (int xvec = -1; xvec < 1; xvec++) {
		for (int yvec = -1; yvec < 1; yvec++) {
			if (checkPosition(x + xvec, y + yvec) && 
				(_board(x, y).getValues(player)[Square::LINK1] 
				|| _board(x, y).getValues(player)[Square::LINK2] 
				|| _board(x, y).getValues(player)[Square::LINK3] 
				|| _board(x, y).getValues(player)[Square::LINK4] 
				|| _board(x, y).getValues(player)[Square::LINK5])
				) 
			{
				return true;
			}
		}
	}
	return false;
}

/*
* Fonction de test de la regle speciale des double 3 pions align�
*/
bool Referee::checkDoubleThree(unsigned int x, unsigned int y, Square::Player& player) {
	for (int xvec = -1; xvec < 1; xvec++) {
		for (int yvec = -1; yvec < 1; yvec++) {
			if (_board(x + xvec, y + yvec).getPlayer() == opponant(player))
				return true;
		}
	}

	if (Link3OrMore(x, y, player) && EndLink2OrMore(x, y, player))
		return false;

	for (int xvec = -1; xvec < 1; xvec++) {
		for (int yvec = -1; yvec < 1; yvec++) {
			if (EndLink2OrMore(x + xvec, y + yvec, player) && !checkNearBlock(x, y, x + xvec, y + yvec, player)) {
				return false;
			}
		}
	}

	return true;
}

/**
* Test si une case a des alignement de 3 ou plus proche
*/
bool Referee::Link3OrMore(unsigned int x, unsigned int y, const Square::Player& player) {
	return (_board(x, y).getValues(player)[Square::LINK3] || _board(x, y).getValues(player)[Square::LINK4] || _board(x, y).getValues(player)[Square::LINK5]);
}

/**
* Test si la case est une fin d'alignement de 2 pions ou plus
*/
bool Referee::EndLink2OrMore(unsigned int x, unsigned int y, const Square::Player& player) {
	return (_board(x, y).getValues(player)[Square::END_LINK2] || _board(x, y).getValues(player)[Square::END_LINK3] || _board(x, y).getValues(player)[Square::END_LINK4] || _board(x, y).getValues(player)[Square::END_LINK5]);
}

/**
* Test si une pierre appartenant au joueurs 'player', est autour des coordonn�e x et y et est a cot� des coordonn�e xorig, yorig
*/
bool Referee::checkNearBlock(unsigned int xorig, unsigned int yorig, unsigned int x, unsigned int y, const Square::Player& player) {\
	for (int xvec = -1; xvec < 1; xvec++) {
		for (int yvec = -1; yvec < 1; yvec++) {
			if ((_board(x + xvec, y + yvec).getPlayer() == player) && (abs((x + xvec) - xorig) > 1 || abs((y + yvec) - yorig) > 1))
				return false;				
		}
	}
	return true;
}




/**
* cherche si il y a une prise dans une direction
*/
bool Referee::checkPrize(unsigned int x, unsigned int y, int xvec, int yvec, const Square::Player& play) {
	unsigned int count = 0;

	do {
		x += xvec;
		y += yvec;
		count++;
	} while ((count <= 2) && checkPosition(x, y) && (_board(x, y).getPlayer() == opponant(play)));

	if (count > 2)
		return (checkPosition(x, y) && (_board(x, y).getPlayer() == play));
	return false;
}

/**
* clean les pierre trouver comme prise
*/
void Referee::cleanRock(unsigned int x, unsigned int y, int xvec, int yvec, const Square::Player& play) {
	for (unsigned int i = 0; i < 2; i++)
	{
		x += xvec;
		y += yvec;
		propagation_inverse(x, y, opponant(play));
	}
}

/**
* get de l'atribut qui contient le gagnant
*/
const Square::Player& Referee::checkWin() const {
	return _winner;
}

/**
* reset le gagnant
*/
void Referee::reset() {
	_winner = Square::NOPLAYER;
}

/* Try to propagate in EVERY directions */
void Referee::propagation(unsigned int x, unsigned int y, const Square::Player& player)
{
	int usize; /* Updated size of (horizontal/vertical/diagonal) line */

	std::cout << " ORG " << x << " " << y << std::endl;
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
}

void Referee::propagation_inverse(unsigned int x, unsigned int y, const Square::Player& player)
{
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
