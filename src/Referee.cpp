/* 
 * File:   Referee.cpp
 * Author: fancel
 *
 * Created on May 5, 2011, 1:14 PM
 */

#include <iostream>

#include "Referee.hpp"
#include "Game.hpp"

Referee::Referee(Board& board)
: _board(board), _winner(0), _fivePrize(false), _doubleThree(false), _winLineList() {
    initDirMap();
}

Referee::Referee(const Referee& orig)
: _board(orig._board), _winner(orig._winner), _fivePrize(orig._fivePrize), _doubleThree(orig._doubleThree), _directionMap(orig._directionMap) {
}

Referee::~Referee() {
}

void Referee::initDirMap() {
    _directionMap[NONE] = DirInfo(NONE, Coord(0, 0), 0, 0);
    _directionMap[RIGHT] = DirInfo(LEFT, Coord(1, 0), &Referee::setHorz, &Referee::getHorz);
    _directionMap[UP_RIGHT] = DirInfo(DOWN_LEFT, Coord(1, -1), &Referee::setDiagr, &Referee::getDiagr);
    _directionMap[UP] = DirInfo(DOWN, Coord(0, -1), &Referee::setVert, &Referee::getVert);
    _directionMap[UP_LEFT] = DirInfo(DOWN_RIGHT, Coord(-1, -1), &Referee::setDiagl, &Referee::getDiagl);
    _directionMap[LEFT] = DirInfo(RIGHT, Coord(-1, 0), &Referee::setHorz, &Referee::getHorz);
    _directionMap[DOWN_LEFT] = DirInfo(UP_RIGHT, Coord(-1, 1), &Referee::setDiagr, &Referee::getDiagr);
    _directionMap[DOWN] = DirInfo(UP, Coord(0, 1), &Referee::setVert, &Referee::getVert);
    _directionMap[DOWN_RIGHT] = DirInfo(UP_LEFT, Coord(1, 1), &Referee::setDiagl, &Referee::getDiagl);
}

/**
 * deplace x et y dans la direction choisie
 */
bool Referee::goTo(unsigned int& x, unsigned int& y, Vector dir) {
    if (dir != NONE) {
        DirMap::iterator it = _directionMap.find(dir);

        if (it != _directionMap.end() && checkPosition(x + it->second.direction.x, y + it->second.direction.y)) {
            x += it->second.direction.x;
            y += it->second.direction.y;
            return true;
        }
    }
    return false;
}

/**
 * Recupere la valeur de l'alignement dans la direction choisie
 */

void Referee::setHorz(Square& square, unsigned int value) {
    square.setRawData(square.getRawData() | HORZ(value));
}

void Referee::setVert(Square& square, unsigned int value) {
    square.setRawData(square.getRawData() | VERT(value));
}

void Referee::setDiagl(Square& square, unsigned int value) {
    square.setRawData(square.getRawData() | DIAGL(value));
}

void Referee::setDiagr(Square& square, unsigned int value) {
    square.setRawData(square.getRawData() | DIAGR(value));
}

unsigned int Referee::getHorz(const Square& square) const {
    return GET_HORZ(square.getRawData());
}

unsigned int Referee::getVert(const Square& square) const {
    return GET_VERT(square.getRawData());
}

unsigned int Referee::getDiagl(const Square& square) const {
    return GET_DIAGL(square.getRawData());
}

unsigned int Referee::getDiagr(const Square& square) const {
    return GET_DIAGR(square.getRawData());
}

unsigned int Referee::getDirAlign(const Square& square, Vector dir) {
    DirMap::iterator it = _directionMap.find(dir);

    if (dir && it != _directionMap.end() && it->second.getter) {
        return (this->*(it->second.getter))(square);
    }
    return 0;
}

void Referee::setDirAlign(Square& square, Vector dir, unsigned int value) {
    DirMap::iterator it = _directionMap.find(dir);

    if (dir && it != _directionMap.end() && it->second.getter) {
        (this->*(it->second.setter))(square, value);
    }
}

/*
 * Teste si la case fait partie d'au moins un alignement superieur ou egale	a 'size'
 */
bool Referee::ispartOfAlign(const Square& value, int size) {
    return (
            GET_DIAGL(value.getRawData()) >= size ||
            GET_DIAGR(value.getRawData()) >= size ||
            GET_HORZ(value.getRawData()) >= size ||
            GET_VERT(value.getRawData()) >= size
            );
}

/*
 * Teste si la case fait partie d'au moins un alignement de 'size'
 */
bool Referee::ispartOfExactAlign(const Square& value, int size) {
    return (
            GET_DIAGL(value.getRawData()) == size ||
            GET_DIAGR(value.getRawData()) == size ||
            GET_HORZ(value.getRawData()) == size ||
            GET_VERT(value.getRawData()) == size
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
        fpropagation(x, y, player);
        value = checkPrize(x, y, player);
        checkIsTakable(x, y, player);
        checkWin(x, y);
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
unsigned int Referee::checkPrize(unsigned int x, unsigned int y, unsigned int player) {
    unsigned int result = 0;

    DirMap::iterator it = _directionMap.begin();
    DirMap::iterator ite = _directionMap.end();

    while (it != ite) {
        if (checkPrize(x, y, it->first, player)) {
            cleanRock(x, y, it->first, player);
            result++;
        }
        ++it;
    }
    return result;
}

/**
 * cherche si il y a une prise dans une direction
 */
bool Referee::checkPrize(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    if (checkCanTake(x, y, dir, player)) {
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

bool Referee::checkCanTake(unsigned x, unsigned int y, Vector dir, unsigned int player) {
    return (goTo(x, y, dir) &&
            (GET_PLAYER(_board(x, y).getRawData()) == opponant(player)) &&
            (getDirAlign(_board(x, y), dir) == 2) && goTo(x, y, dir) && goTo(x, y, dir));
}

/**
 * clean les pierre trouver comme prise
 */
void Referee::cleanRock(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    unsigned int xtmp, ytmp;

    goTo(x, y, dir);
    std::cout << "## x " << x << " ## y " << y << std::endl;
    _board(x, y).setRawData(0);
    xtmp = x;
    ytmp = y;

    goTo(x, y, dir);
    std::cout << "## x " << x << " ## y " << y << std::endl;
    _board(x, y).setRawData(0);

    fpropagation_inverse(xtmp, ytmp, opponant(player));
    fpropagation_inverse(x, y, opponant(player));
}

void Referee::checkIsTakable(unsigned int x, unsigned int y, unsigned int player) {
    if (ispartOfExactAlign(_board(x, y), 2)) {
        DirMap::iterator it = _directionMap.begin();
        DirMap::iterator ite = _directionMap.end();

        while (it != ite) {
            if (checkIsTakable(x, y, it->first, player)) {
                unsigned int xtmp = x;
                unsigned int ytmp = y;
                
                _board(x, y).setRawData(_board(x, y).getRawData() | IS_TAKABLE(1));
                goTo(xtmp, ytmp, it->first);
                _board(xtmp, ytmp).setRawData(_board(xtmp, ytmp).getRawData() | IS_TAKABLE(1));
            }
            ++it;
        }
    }
}

bool Referee::checkIsTakable(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    unsigned int xinv = x;
    unsigned int yinv = y;
    
    return (getDirAlign(_board(x, y), dir) == 2 && goTo(xinv, yinv, invert(dir)) && goTo(x, y, dir) && goTo(x, y, dir) &&
            ((GET_PLAYER(_board(xinv, yinv).getRawData()) == opponant(player) || GET_PLAYER(_board(x, y).getRawData()) == opponant(player)) && !(GET_PLAYER(_board(xinv, yinv).getRawData()) == opponant(player) && GET_PLAYER(_board(x, y).getRawData()) == opponant(player))));
}

/**
 * Determine si le coup est gagnant
 */
void Referee::checkWin(unsigned int x, unsigned int y) {
    if (ispartOfAlign(_board(x, y), 5)) {
        _winLineList.push_back(Coord(x, y));
        _board(x, y).dumpData();
        checkWinList();
    }
}

void Referee::checkWinList() {
    WinList::iterator it = _winLineList.begin();
    WinList::iterator ite = _winLineList.end();

    while (it != ite && ispartOfAlign(_board(it->x, it->y), 5)) {
        if (_fivePrize) {
            if (checkFivePrize(it->x, it->y))
                _winner = GET_PLAYER(_board(it->x, it->y).getRawData());
        } else {
            _winner = GET_PLAYER(_board(it->x, it->y).getRawData());
        }
        ++it;
    }
    if (it != ite) {
        _winLineList.erase(it);
        checkWinList();
    }

}

/**
 * Fonction de test de la regle speciale des 5 pions lors d'une tentative de victoire
 */
bool Referee::checkFivePrize(unsigned int x, unsigned int y) {
    unsigned int player = GET_PLAYER(_board(x, y).getRawData());

    if (GET_DIAGL(_board(x, y).getRawData()) > 4) {
        unsigned int size = checkFivePrize(x, y, UP_LEFT, player);
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
    for (unsigned int i = 0; i < _directionMap.size() && num < 2; i++) {
        num += isPartOfFree3Align(x, y, static_cast<Vector> (i), player);
    }

    if (num >= 2)
        return false;
    return true;
}

unsigned int Referee::isPartOfFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    unsigned int xnear = x;
    unsigned int ynear = y;

    if (goTo(xnear, ynear, invert(dir)) && GET_PLAYER(_board(xnear, ynear).getRawData()) != opponant(player)) {
        return classicFree3Align(x, y, dir, player) + unClassicFree3Align(x, y, dir, player);
    }
    return 0;
}

unsigned int Referee::classicFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    int value = 0;
    if (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player) {
        value += isPartOfAlign3InOther(x, y, dir, player);

        if (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player) {
            value += isPartOfAlign3InOther(x, y, dir, player);

            if (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) != opponant(player))
                return value + 1;
        }
    }
    return 0;
}

unsigned int Referee::unClassicFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    unsigned int value = 0;

    if (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == 0 &&
            goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player) {
        value += isPartOfAlign3InOther(x, y, dir, player);

        if (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player) {
            value += isPartOfAlign3InOther(x, y, dir, player);

            if (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) != opponant(player))
                return value + 1;
        }
    }
    return 0;
}

unsigned int Referee::isPartOfAlign3InOther(unsigned x, unsigned int y, Vector dir, unsigned int player) {
    if (ispartOfExactAlign(_board(x, y), 3)) {
        unsigned int value = 0;

        if (isFreeAlign(x, y, dir, UP_RIGHT, player))
            value++;

        if (isFreeAlign(x, y, dir, UP_LEFT, player))
            value++;

        if (isFreeAlign(x, y, dir, UP, player))
            value++;

        if (isFreeAlign(x, y, dir, LEFT, player))
            value++;
        return value;
    }
    return 0;
}

bool Referee::isFreeAlign(unsigned int x, unsigned int y, Vector dirorig, Vector dir, unsigned int player) {

    if (dirorig != dir && dir != invert(dir)) {
        unsigned int xtmp = x;
        unsigned int ytmp = y;
        unsigned int size = 1;

        while (goTo(xtmp, ytmp, dir) && GET_PLAYER(_board(xtmp, ytmp).getRawData()) == player)
            size++;

        if (GET_PLAYER(_board(xtmp, ytmp).getRawData()) == 0) {
            xtmp = x;
            ytmp = y;

            while (goTo(xtmp, ytmp, invert(dir)) && GET_PLAYER(_board(xtmp, ytmp).getRawData()) == player)
                size++;

            if (size > 2 && GET_PLAYER(_board(xtmp, ytmp).getRawData()) == 0)
                return true;
        }
    }
    return false;
}

/* Try to propagate in EVERY directions */

void Referee::propagation(unsigned int x, unsigned int y, unsigned int player) {

    int usize; // Updated size of (horizontal/vertical/diagonal) line

    std::cout << " ORG " << x << " " << y << std::endl;
    if (checkPosition(x, y + 1))
        _board(x, y).getData().vert = _board(x, y + 1).getData().vert;
    if (checkPosition(x, y - 1))
        _board(x, y).getData().vert += _board(x, y - 1).getData().vert;
    usize = _board(x, y).getData().vert += 1;

    propagation(x, y, player, DIR_UP, usize);
    propagation(x, y, player, DIR_DOWN, usize);

    //usize = _board(x, y)._horz = _board(x-1, y)._horz + _board(x+1, y)._horz + 1;

    if (checkPosition(x - 1, y))
        _board(x, y).getData().horz = _board(x - 1, y).getData().horz;
    if (checkPosition(x + 1, y))
        _board(x, y).getData().horz += _board(x + 1, y).getData().horz;
    usize = _board(x, y).getData().horz += 1;

    propagation(x, y, player, DIR_LEFT, usize);
    propagation(x, y, player, DIR_RIGHT, usize);

    if (checkPosition(x - 1, y - 1))
        _board(x, y).getData().diagl = _board(x - 1, y - 1).getData().diagl;
    if (checkPosition(x + 1, y + 1))
        _board(x, y).getData().diagl += _board(x + 1, y + 1).getData().diagl;
    usize = _board(x, y).getData().diagl += 1;

    propagation(x, y, player, DIR_UP | DIR_LEFT, usize);
    propagation(x, y, player, DIR_DOWN | DIR_RIGHT, usize);

    if (checkPosition(x + 1, y - 1))
        _board(x, y).getData().diagr = _board(x + 1, y - 1).getData().diagr;
    if (checkPosition(x - 1, y + 1))
        _board(x, y).getData().diagr += _board(x - 1, y + 1).getData().diagr;
    usize = _board(x, y).getData().diagr += 1;

    propagation(x, y, player, DIR_UP | DIR_RIGHT, usize);
    propagation(x, y, player, DIR_DOWN | DIR_LEFT, usize);
}

/* Try to propagate in ONE direction */
void Referee::propagation(unsigned int x, unsigned int y, unsigned int player,
        unsigned int dir, unsigned int usize) {
    int i = 0x8;

    do
        switch (dir & i) {
            case DIR_UP: y--;
                break;
            case DIR_DOWN: y++;
                break;
            case DIR_LEFT: x--;
                break;
            case DIR_RIGHT: x++;
                break;
            default: break;
        } while ((i >>= 1));

    if (checkPosition(x, y) && GET_PLAYER(_board(x, y).getRawData()) == player) {
        std::cout << "  IN " << x << " " << y << "  usize(" << usize << ")" << std::endl;
        switch (dir) {
            case DIR_UP: _board(x, y).getData().vert = usize;
                break;
            case DIR_DOWN: _board(x, y).getData().vert = usize;
                break;
            case DIR_LEFT: _board(x, y).getData().horz = usize;
                break;
            case DIR_RIGHT: _board(x, y).getData().horz = usize;
                break;
            case DIR_UP | DIR_LEFT: _board(x, y).getData().diagl = usize;
                break;
            case DIR_DOWN | DIR_RIGHT: _board(x, y).getData().diagl = usize;
                break;
            case DIR_UP | DIR_RIGHT: _board(x, y).getData().diagr = usize;
                break;
            case DIR_DOWN | DIR_LEFT: _board(x, y).getData().diagr = usize;
                break;
            default: break;
        }
        propagation(x, y, player, dir, usize);
    }
}

void Referee::propagation_inverse(unsigned int x, unsigned int y, unsigned int player) {
    int usize1;
    int usize2;

    std::cout << " ORG " << x << " " << y << "    <- INVERSE" << std::endl;
    usize1 = lineSize(x, y, player, DIR_UP);
    usize2 = _board(x, y).getData().vert - usize1 - 1;
    propagation(x, y, player, DIR_UP, usize1);
    propagation(x, y, player, DIR_DOWN, usize2);

    usize1 = lineSize(x, y, player, DIR_LEFT);
    usize2 = _board(x, y).getData().horz - usize1 - 1;
    propagation(x, y, player, DIR_LEFT, usize1);
    propagation(x, y, player, DIR_RIGHT, usize2);

    usize1 = lineSize(x, y, player, DIR_UP | DIR_LEFT);
    usize2 = _board(x, y).getData().diagl - usize1 - 1;
    propagation(x, y, player, DIR_UP | DIR_LEFT, usize1);
    propagation(x, y, player, DIR_DOWN | DIR_RIGHT, usize2);

    usize1 = lineSize(x, y, player, DIR_UP | DIR_RIGHT);
    usize2 = _board(x, y).getData().diagr - usize1 - 1;
    propagation(x, y, player, DIR_UP | DIR_RIGHT, usize1);
    propagation(x, y, player, DIR_DOWN | DIR_LEFT, usize2);

    _board(x, y).getData().horz = 0;
    _board(x, y).getData().vert = 0;
    _board(x, y).getData().diagl = 0;
    _board(x, y).getData().diagr = 0;
    _board(x, y).getData().player = NOPLAYER;
}

int Referee::lineSize(unsigned int x, unsigned int y, unsigned int player, int dir) {
    int i = 0x8;

    do
        switch (dir & i) {
            case DIR_UP: y--;
                break;
            case DIR_DOWN: y++;
                break;
            case DIR_LEFT: x--;
                break;
            case DIR_RIGHT: x++;
                break;
            default: break;
        } while ((i >>= 1));

    if (GET_PLAYER(_board(x, y).getRawData()) == player)
        return lineSize(x, y, player, dir) + 1;
    return 0;
}

void Referee::fpropagation(unsigned int x, unsigned int y, const unsigned int player) {
    fpropagation(x, y, UP, player);
    fpropagation(x, y, LEFT, player);
    fpropagation(x, y, UP_RIGHT, player);
    fpropagation(x, y, UP_LEFT, player);
}

void Referee::fpropagation(unsigned int x, unsigned int y, Vector dir, const unsigned int player) {
    unsigned int lineSize = 0;

    lineSize = flineSize(x, y, dir, player) + flineSize(x, y, invert(dir), player) + 1;
    fsetline(x, y, dir, player, lineSize);
    fsetline(x, y, invert(dir), player, lineSize);
    setDirAlign(_board(x, y), dir, lineSize);
}

void Referee::fpropagation_inverse(unsigned int x, unsigned int y, const unsigned int player) {
    for (unsigned int i = 0; i < _directionMap.size(); i++)
        fpropag_inverse_to(x, y, static_cast<Vector> (i), player);
}

void Referee::fpropag_inverse_to(unsigned int x, unsigned int y, Vector dir, const unsigned int player) {
    if (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player)
        fpropagation(x, y, player);
}

std::size_t Referee::flineSize(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    std::size_t i = 0;

    while (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player)
        i++;

    return i;
}

void Referee::fsetline(unsigned int x, unsigned int y, Vector dir, unsigned int player, unsigned int value) {
    while (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player) {
        setDirAlign(_board(x, y), dir, value);
    }
}
