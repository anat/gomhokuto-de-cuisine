
#include <iostream>
#include "RefereeManager.hpp"

RefereeManager::RefereeManager() : _directionMap(), _mapSize(), _fivePrize(false), _doubleThree(false)
{
    _directionArray[NONE] = DirInfo();
    _directionArray[RIGHT] = DirInfo(LEFT, Coord(1, 0), &Square::setHorz, &Square::getHorz, &Square::getHorzBlock, &Square::setHorzBlock);
    _directionArray[UP_RIGHT] = DirInfo(DOWN_LEFT, Coord(1, -1), &Square::setDiagr, &Square::getDiagr, &Square::getDiagrBlock, &Square::setDiagrBlock);
    _directionArray[UP] = DirInfo(DOWN, Coord(0, -1), &Square::setVert, &Square::getVert, &Square::getVertBlock, &Square::setVertBlock);
    _directionArray[UP_LEFT] = DirInfo(DOWN_RIGHT, Coord(-1, -1), &Square::setDiagl, &Square::getDiagl, &Square::getDiaglBlock, &Square::setDiaglBlock);
    _directionArray[LEFT] = DirInfo(RIGHT, Coord(-1, 0), &Square::setHorz, &Square::getHorz, &Square::getHorzBlock, &Square::setHorzBlock);
    _directionArray[DOWN_LEFT] = DirInfo(UP_RIGHT, Coord(-1, 1), &Square::setDiagr, &Square::getDiagr, &Square::getDiagrBlock, &Square::setDiagrBlock);
    _directionArray[DOWN] = DirInfo(UP, Coord(0, 1), &Square::setVert, &Square::getVert, &Square::getVertBlock, &Square::setVertBlock);
    _directionArray[DOWN_RIGHT] = DirInfo(UP_LEFT, Coord(1, 1), &Square::setDiagl, &Square::getDiagl, &Square::getDiaglBlock, &Square::setDiaglBlock);

    _mapSize = _directionMap.size();

    _vectorArray[NONE] = NONE;
    _vectorArray[RIGHT] = RIGHT;
    _vectorArray[UP_RIGHT] = UP_RIGHT;
    _vectorArray[UP] = UP;
    _vectorArray[UP_LEFT] = UP_LEFT;
    _vectorArray[LEFT] = LEFT;
    _vectorArray[DOWN_LEFT] = DOWN_LEFT;
    _vectorArray[DOWN] = DOWN;
    _vectorArray[DOWN_RIGHT] = DOWN_RIGHT;

}

RefereeManager::RefereeManager(const RefereeManager &orig)
    : _directionMap(orig._directionMap), _vectorArray(orig._vectorArray), _directionArray(orig._directionArray), _fivePrize(orig._fivePrize), _doubleThree(orig._doubleThree)
{}

unsigned int RefereeManager::size() const
{
    return _vectorArray.size();
}

bool RefereeManager::fivePrize() const
{
    return _fivePrize;
}

bool RefereeManager::doubleThree() const
{
    return _doubleThree;
}

void RefereeManager::setDoubleThree(bool value)
{
    _doubleThree = value;
}

const RefereeManager::VectorArray& RefereeManager::getVectorArray() const {
    return _vectorArray;
}

const RefereeManager::DirInfo& RefereeManager::getInfo(const Vector &dir) const {
    return _directionArray[dir];
}

void RefereeManager::setFivePrize(bool value)
{
    _fivePrize = value;
}

RefereeManager::Vector RefereeManager::invert(const Vector &dir) const {
    if (dir != NONE) {
        return _directionArray[dir].invert;
    }
    return NONE;
}

bool RefereeManager::goTo(unsigned int boardSize, unsigned int& x, unsigned int& y, Vector dir) {
    if (dir != RefereeManager::NONE && checkPosition(x + _directionArray[dir].direction.x, y + _directionArray[dir].direction.y, boardSize)) {
        x += _directionArray[dir].direction.x;
        y += _directionArray[dir].direction.y;
        return true;
    }
    return false;
}

unsigned int RefereeManager::getDirAlign(const Square& square, Vector dir) const {
    if (dir != RefereeManager::NONE && _directionArray[dir].getter) {
            return (square.*(_directionArray[dir].getter))();
    }
    return 0;
}

void RefereeManager::setDirAlign(Square& square, Vector dir, unsigned int lineSize) const {
    if (dir != RefereeManager::NONE && _directionArray[dir].setter) {
        (square.*(_directionArray[dir].setter))(lineSize);
    }
}

unsigned int RefereeManager::getDirEnd(const Square &square, Vector dir) const {
    if (dir != RefereeManager::NONE && _directionArray[dir].getEndBlock) {
        return (square.*(_directionArray[dir].getEndBlock))();
    }
    return 0;
}

void RefereeManager::setDirEnd(Square &square, Vector dir, unsigned int endBlockValue) const {
    if (dir != RefereeManager::NONE && _directionArray[dir].setEndBlock) {
            (square.*(_directionArray[dir].setEndBlock))(endBlockValue);
    }
}
