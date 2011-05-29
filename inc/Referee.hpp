/* 
 * File:   Referee.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 1:14 PM
 */

#ifndef REFEREE_HPP
#define	REFEREE_HPP

#include <vector>
#include <list>
#include <map>

#include "Board.hpp"

#define DIR_UP    0x1
#define DIR_DOWN  0x2
#define DIR_LEFT  0x4
#define DIR_RIGHT 0x8

/*
 * L'arbitre
 */
struct Coord {

    Coord(int x_, int y_) : x(x_), y(y_) {
    }

    Coord & operator+(const Coord & value) {
        x += value.x;
        y += value.y;
        return (*this);
    }
    int x;
    int y;
};

class Referee {
public:
    Referee(Board& board);
    Referee(const Referee& orig);
    virtual ~Referee();

    int tryPlaceRock(unsigned int x, unsigned int y, unsigned int square); //Test et si ok place
    bool testPosition(unsigned int x, unsigned int y, unsigned int player); //Test tout cours
    unsigned int checkWin() const;
    bool doubleThree() const;
    bool fivePrize() const;
    bool doubleThree(bool value);
    bool fivePrize(bool value);
    void reset();

private:

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

    typedef void (Referee::*setDirFunc)(Square&, unsigned int);
    typedef unsigned int (Referee::*getDirFunc)(const Square&) const;

    struct DirInfo {

        DirInfo(const Vector& inv, const Coord& dir, setDirFunc set, getDirFunc get)
        : invert(inv), direction(dir), setter(set), getter(get) {
        }

        DirInfo()
        : invert(NONE), direction(Coord(0, 0)), setter(0), getter(0) {
        }

        Vector invert;
        Coord direction;
        setDirFunc setter;
        getDirFunc getter;
    };

    typedef std::list<Coord> WinList;
    typedef std::map<Vector, DirInfo> DirMap;

    Board& _board;
    unsigned int _winner;
    bool _fivePrize;
    bool _doubleThree;
    WinList _winLineList;
    DirMap _directionMap;

    inline unsigned int opponant(const unsigned int pla) {
        unsigned int result = 0;
        if (pla == 1)
            result = 2;
        else if (pla == 2)
            result = 1;
        return result;
    }

    inline bool checkPosition(unsigned int x, unsigned int y) {
        return (x < _board.getSize() && y < _board.getSize());
    }

    inline unsigned int abs(int value) {
        if (value < 0)
            return value * -1;
        return value;
    }

    inline Vector invert(Vector dir) {
        DirMap::iterator it = _directionMap.find(dir);

        if (it != _directionMap.end())
            return it->second.invert;
        return NONE;
    }

    void initDirMap();
    bool goTo(unsigned int& x, unsigned int& y, Vector dir);
    unsigned int getDirAlign(const Square& value, Vector dir);
    void setDirAlign(Square& square, Vector dir, unsigned int value);
    bool ispartOfAlign(const Square& value, int size);
    bool ispartOfExactAlign(const Square& value, int size);

    void setHorz(Square& square, unsigned int value);
    void setVert(Square& square, unsigned int value);
    void setDiagl(Square& square, unsigned int value);
    void setDiagr(Square& square, unsigned int value);

    unsigned int getHorz(const Square& square) const;
    unsigned int getVert(const Square& square) const;
    unsigned int getDiagl(const Square& square) const;
    unsigned int getDiagr(const Square& square) const;

    /*
     * Fonction de check pour les double alignement de trois
     */
    bool checkDoubleThree(unsigned int x, unsigned int y, unsigned int player);
    unsigned int isPartOfFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    unsigned int classicFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    unsigned int unClassicFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    unsigned int isPartOfAlign3InOther(unsigned x, unsigned int y, Vector dir, unsigned int player);
    bool isFreeAlign(unsigned int x, unsigned int y, Vector dirorig, Vector dir, unsigned int player);

    /*
     * Fonction pour la victoire par alignement de 5
     */
    void checkWin(unsigned int x, unsigned int y);
    void checkWinList();
    void checkIsTakable(unsigned int x, unsigned int y, unsigned int player);
    bool checkIsTakable(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    bool checkIsTakableInvert(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    bool checkfiveWin(unsigned int x, unsigned int y);
    bool checkFivePrize(unsigned int x, unsigned int y);
    unsigned int checkFivePrize(unsigned int x, unsigned int y, Vector dir, unsigned int player);

    /*
     * Fonction pour la prise de pierre
     */
    unsigned int checkPrize(unsigned int x, unsigned int y, const unsigned int player);
    bool checkPrize(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    bool checkCanTake(unsigned x, unsigned int y, Vector dir, unsigned int player);
    void cleanRock(unsigned int x, unsigned int y, Vector dir, unsigned int player);

    /*
     * Fonction pour la propagation
     */

    void propagation(unsigned int x, unsigned int y, const unsigned int player);
    void propagation(unsigned int x, unsigned int y, const unsigned int player,
            unsigned int dir, unsigned int usize);
    void propagation_inverse(unsigned int x, unsigned int y, const unsigned int player);
    int lineSize(unsigned int x, unsigned int y, const unsigned int player, int dir);

    /*
     * Fonction de propagation fait par fancel
     */

    void fpropagation(unsigned int x, unsigned int y, const unsigned int player);
    void fpropagation(unsigned int x, unsigned int y, Vector dir, const unsigned int player);
    void fpropagation_inverse(unsigned int x, unsigned int y, const unsigned int player);
    void fpropag_inverse_to(unsigned int x, unsigned int y, Vector dir, const unsigned int player);
    std::size_t flineSize(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    void fsetline(unsigned int x, unsigned int y, Vector dir, unsigned int player, unsigned int value);
};

#endif	/* REFEREE_HPP */

