
#include <iostream>
#include "RefereeManager.hpp"

RefereeManager::RefereeManager() : _directionMap(), _mapSize(), _fivePrize(false), _doubleThree(false)
{
    //std::cout << "CACA" << std::endl;
    _directionMap[NONE] = DirInfo(NONE, Coord(0, 0), 0, 0);
    _directionMap[RIGHT] = DirInfo(LEFT, Coord(1, 0), &Square::setHorz, &Square::getHorz);
    _directionMap[UP_RIGHT] = DirInfo(DOWN_LEFT, Coord(1, -1), &Square::setDiagr, &Square::getDiagr);
    _directionMap[UP] = DirInfo(DOWN, Coord(0, -1), &Square::setVert, &Square::getVert);
    _directionMap[UP_LEFT] = DirInfo(DOWN_RIGHT, Coord(-1, -1), &Square::setDiagl, &Square::getDiagl);
    _directionMap[LEFT] = DirInfo(RIGHT, Coord(-1, 0), &Square::setHorz, &Square::getHorz);
    _directionMap[DOWN_LEFT] = DirInfo(UP_RIGHT, Coord(-1, 1), &Square::setDiagr, &Square::getDiagr);
    _directionMap[DOWN] = DirInfo(UP, Coord(0, 1), &Square::setVert, &Square::getVert);
    _directionMap[DOWN_RIGHT] = DirInfo(UP_LEFT, Coord(1, 1), &Square::setDiagl, &Square::getDiagl);

    _mapSize = _directionMap.size();

    DirMap::iterator it = _directionMap.begin();
    DirMap::iterator ite = _directionMap.end();

//    while (it != ite) {
//        std::cout << "x " << it->second.direction.x << " y " << it->second.direction.y << std::endl;
//        ++it;
//    }
    //std::cout << "CACA" << std::endl;
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
    DirMap::const_iterator it = _directionMap.find(dir);

    if (dir && it != _directionMap.end() && it->second.getter) {
        return (square.*(it->second.getter))();
    }
    return 0;
}

void RefereeManager::setDirAlign(Square& square, Vector dir, unsigned int lineSize) const {
    DirMap::const_iterator it = _directionMap.find(dir);

    if (dir && it != _directionMap.end() && it->second.getter) {
        (square.*(it->second.setter))(lineSize);
    }
}
