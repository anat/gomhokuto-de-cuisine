#ifndef REFEREEMANAGER_HPP
#define REFEREEMANAGER_HPP

/*
  paramettre qui geree l'ensemble des Referee
*/

#include <map>

#include "Coord.hpp"
#include "Singleton.hpp"
#include "Square.hpp"

class RefereeManager : public Singleton<RefereeManager>
{
    SINGLETON_CLASS(RefereeManager);

public:
    typedef void (Square::*setDirFunc)(unsigned int);
    typedef unsigned int (Square::*getDirFunc)() const;

    enum Vector {
        NONE,
        RIGHT,
        UP_RIGHT,
        UP,
        UP_LEFT,
        LEFT,
        DOWN_LEFT,
        DOWN,
        DOWN_RIGHT
    };

    struct DirInfo {

        DirInfo(const Vector& inv, const Coord& dir, setDirFunc set, getDirFunc get)
        : invert(inv), direction(dir), setter(set), getter(get)
        {}

        DirInfo()
        : invert(NONE), direction(Coord(0, 0)), setter(0), getter(0)
        {}

        Vector invert;
        Coord direction;
        setDirFunc setter;
        getDirFunc getter;
    };

    typedef std::map<Vector, DirInfo> DirMap;

    DirMap::iterator find(Vector& value);
    DirMap::iterator begin();
    DirMap::iterator end();

    DirMap::const_iterator find(Vector& value) const;
    DirMap::const_iterator begin() const;
    DirMap::const_iterator end() const;

    unsigned int size() const;
    bool fivePrize() const;
    bool doubleThree() const;
    void setFivePrize(bool value);
    void setDoubleThree(bool value);

private:
    DirMap _directionMap;
    unsigned int _mapSize;
    bool _fivePrize;
    bool _doubleThree;

    RefereeManager();
    RefereeManager(const RefereeManager& orig);
};

#endif // REFEREEMANAGER_HPP
