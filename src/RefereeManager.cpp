
#include <iostream>
#include "RefereeManager.hpp"

RefereeManager::RefereeManager() : _directionMap(), _mapSize(), _fivePrize(false), _doubleThree(false)
{
    _directionMap[NONE] = DirInfo();
    _directionMap[RIGHT] = DirInfo(LEFT, Coord(1, 0), &Square::setHorz, &Square::getHorz, &Square::getHorzBlock, &Square::setHorzBlock);
    _directionMap[UP_RIGHT] = DirInfo(DOWN_LEFT, Coord(1, -1), &Square::setDiagr, &Square::getDiagr, &Square::getDiagrBlock, &Square::setDiagrBlock);
    _directionMap[UP] = DirInfo(DOWN, Coord(0, -1), &Square::setVert, &Square::getVert, &Square::getVertBlock, &Square::setVertBlock);
    _directionMap[UP_LEFT] = DirInfo(DOWN_RIGHT, Coord(-1, -1), &Square::setDiagl, &Square::getDiagl, &Square::getDiaglBlock, &Square::setDiaglBlock);
    _directionMap[LEFT] = DirInfo(RIGHT, Coord(-1, 0), &Square::setHorz, &Square::getHorz, &Square::getHorzBlock, &Square::setHorzBlock);
    _directionMap[DOWN_LEFT] = DirInfo(UP_RIGHT, Coord(-1, 1), &Square::setDiagr, &Square::getDiagr, &Square::getDiagrBlock, &Square::setDiagrBlock);
    _directionMap[DOWN] = DirInfo(UP, Coord(0, 1), &Square::setVert, &Square::getVert, &Square::getVertBlock, &Square::setVertBlock);
    _directionMap[DOWN_RIGHT] = DirInfo(UP_LEFT, Coord(1, 1), &Square::setDiagl, &Square::getDiagl, &Square::getDiaglBlock, &Square::setDiaglBlock);

    _mapSize = _directionMap.size();
}

RefereeManager::RefereeManager(const RefereeManager &orig)
    : _directionMap(orig._directionMap), _fivePrize(orig._fivePrize), _doubleThree(orig._doubleThree)
{}

unsigned int RefereeManager::size() const
{
    return _mapSize;
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

void RefereeManager::setFivePrize(bool value)
{
    _fivePrize = value;
}

RefereeManager::DirMap& RefereeManager::map()
{
    return _directionMap;
}

const RefereeManager::DirMap& RefereeManager::map() const
{
    return _directionMap;
}

RefereeManager::Vector RefereeManager::invert(const Vector &dir) const {
    if (dir != NONE) {
        DirMap::const_iterator it = _directionMap.find(dir);

        if (it != _directionMap.end()) {
            return it->second.invert;
        }
    }
    return NONE;
}

bool RefereeManager::goTo(unsigned int boardSize, unsigned int& x, unsigned int& y, Vector dir) {
    if (dir != RefereeManager::NONE) {
        DirMap::const_iterator it = _directionMap.find(dir);

        if (it != _directionMap.end() && checkPosition(x + it->second.direction.x, y + it->second.direction.y, boardSize)) {
            x += it->second.direction.x;
            y += it->second.direction.y;
            return true;
        }
    }
    return false;
}

unsigned int RefereeManager::getDirAlign(const Square& square, Vector dir) const {
    if (dir != RefereeManager::NONE) {
        DirMap::const_iterator it = _directionMap.find(dir);

        if (it != _directionMap.end() && it->second.getter) {
            return (square.*(it->second.getter))();
        }
    }
    return 0;
}

void RefereeManager::setDirAlign(Square& square, Vector dir, unsigned int lineSize) const {
    if (dir != RefereeManager::NONE) {
        DirMap::const_iterator it = _directionMap.find(dir);

        if (it != _directionMap.end() && it->second.setter) {
            (square.*(it->second.setter))(lineSize);
        }
    }
}

unsigned int RefereeManager::getDirEnd(const Square &square, Vector dir) const {
    if (dir != RefereeManager::NONE) {
        DirMap::const_iterator it = _directionMap.find(dir);

        if (it != _directionMap.end() && it->second.getEndBlock) {
            return (square.*(it->second.getEndBlock))();
        }
    }

    return 0;
}

void RefereeManager::setDirEnd(Square &square, Vector dir, unsigned int endBlockValue) const {
    if (dir != RefereeManager::NONE) {
        DirMap::const_iterator it = _directionMap.find(dir);

        if (it != _directionMap.end() && it->second.setEndBlock) {
            (square.*(it->second.setEndBlock))(endBlockValue);
        }
    }
}
