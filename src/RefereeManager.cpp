
#include "RefereeManager.hpp"

RefereeManager::RefereeManager() : _fivePrize(false), _doubleThree(false)
{
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
}

RefereeManager::RefereeManager(const RefereeManager &orig)
    : _directionMap(orig._directionMap), _fivePrize(orig._fivePrize), _doubleThree(orig._doubleThree)
{}

RefereeManager::DirMap::iterator RefereeManager::find(Vector &value)
{
    return _directionMap.find(value);
}

RefereeManager::DirMap::const_iterator RefereeManager::find(Vector &value) const
{
    return _directionMap.find(value);
}

RefereeManager::DirMap::iterator RefereeManager::begin()
{
    return _directionMap.begin();
}

RefereeManager::DirMap::const_iterator RefereeManager::begin() const
{
    return _directionMap.begin();
}

RefereeManager::DirMap::iterator RefereeManager::end()
{
    return _directionMap.end();
}

RefereeManager::DirMap::const_iterator RefereeManager::end() const
{
    return _directionMap.end();
}

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
