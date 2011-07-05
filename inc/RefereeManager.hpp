#ifndef REFEREEMANAGER_HPP
#define REFEREEMANAGER_HPP

/*
  paramettre qui geree l'ensemble des Referee
*/

#include <map>

#include "Array.hpp"
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

        DirInfo(const Vector& inv, const Coord& dir, setDirFunc set, getDirFunc get, getDirFunc getEnd, setDirFunc setEnd)
            : invert(inv), direction(dir), setter(set), getter(get), getEndBlock(getEnd), setEndBlock(setEnd)
        {
            //std::cout << "DirInfo x " << direction.x << " y " << direction.y << std::endl;
        }

        DirInfo()
            : invert(NONE), direction(Coord(0, 0)), setter(0), getter(0), getEndBlock(0), setEndBlock(0)
        {}

        Vector invert;
        Coord direction;
        setDirFunc setter;
        getDirFunc getter;
        getDirFunc getEndBlock;
        setDirFunc setEndBlock;
    };

    typedef std::map<Vector, DirInfo> DirMap;
    typedef Array<Vector, 9> VectorArray;
    typedef Array<DirInfo, 9> InfoArray;

    unsigned int size() const;
    bool fivePrize() const;
    bool doubleThree() const;
    void setFivePrize(bool value);
    void setDoubleThree(bool value);
    const VectorArray& getVectorArray() const;
    const DirInfo& getInfo(const Vector& dir) const;
    Vector invert(const Vector& dir) const;
    bool goTo(unsigned int boardSize, unsigned int& x, unsigned int& y, Vector dir);
    unsigned int getDirAlign(const Square& square, Vector dir) const;
    unsigned int getDirEnd(const Square& square, Vector dir) const;
    void setDirAlign(Square& square, Vector dir, unsigned int lineSize) const;
    void setDirEnd(Square& square, Vector dir, unsigned int endBlockValue) const;


private:
    DirMap _directionMap;
    VectorArray _vectorArray;
    InfoArray _directionArray;
    unsigned int _mapSize;
    bool _fivePrize;
    bool _doubleThree;

    RefereeManager();
    RefereeManager(const RefereeManager& orig);

    inline bool checkPosition(unsigned int x, unsigned int y, unsigned int size) {
        return (x < size && y < size);
    }
};

#endif // REFEREEMANAGER_HPP
