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
#include <iostream>

#include "Board.hpp"
#include "Coord.hpp"
#include "RefereeManager.hpp"
#include "ThreeAlignChecker.hpp"

#define DIR_UP    0x1
#define DIR_DOWN  0x2
#define DIR_LEFT  0x4
#define DIR_RIGHT 0x8

/**
 * L'arbitre
 */

class Referee {
public:
    typedef RefereeManager::Vector Vector;

    Referee(Board& board);
    Referee(const Referee& orig);
    Referee(const Referee& orig, Board& board);
    virtual ~Referee();

    int tryPlaceRock(unsigned int x, unsigned int y, unsigned int player); //Test et si ok place
    bool testPosition(unsigned int x, unsigned int y, unsigned int player); //Test tout cours
    unsigned int checkWin() const;
    bool doubleThree() const;
    bool fivePrize() const;
    bool doubleThree(bool value);
    bool fivePrize(bool value);
    void reset();
    unsigned int getScore(unsigned int player);

    static inline unsigned int opponant(const unsigned int pla) {
        unsigned int result = 0;
        if (pla == 1)
            result = 2;
        else if (pla == 2)
            result = 1;
        return result;
    }

    inline const Board& getBoard() {
        return _board;
    }

private:
    struct PropagationInfo {
        std::size_t lineSize;
        unsigned int endBlock;

        PropagationInfo() : lineSize(0), endBlock(0) {}

        PropagationInfo& operator+(const PropagationInfo& buddy) {
            lineSize += buddy.lineSize;
            endBlock += buddy.endBlock;
            return *this;
        }
    };

    typedef std::list<Coord> WinList;

    WinList _winLineList;
    Board& _board;
    ThreeAlignChecker _threeChecker;
    Array< unsigned int, 2 > _score;
    unsigned int _winner;

    inline bool checkPosition(unsigned int x, unsigned int y) const {
        return (x < _board.getSize() && y < _board.getSize());
    }

    void setScore(unsigned int player, unsigned int value);

    bool goTo(unsigned int& x, unsigned int& y, Vector dir) const;
    unsigned int getDirAlign(const Square& value, Vector dir) const;
    void setDirAlign(Square& square, Vector dir, unsigned int value);
    unsigned int getDirEnd(const Square& square, Vector dir) const;
    void setDirEnd(Square& square, Vector dir, unsigned int endValue);
    bool ispartOfAlign(const Square& value, unsigned int size);
    bool ispartOfExactAlign(const Square& value, int size);
    void setTakable(Square& square, bool value);

    /*
     * Fonction de check pour les double alignement de trois
     */

    bool checkDoubleThree(unsigned int x, unsigned int y, unsigned int player);

    /*
     * Fonction pour la victoire par alignement de 5
     */
    void checkWin(unsigned int x, unsigned int y, unsigned int player);
    void checkWinList();
    void checkIsTakable(unsigned int x, unsigned int y, unsigned int player);
    bool checkIsTakable(unsigned int x, unsigned int y, Vector dir, unsigned int player) const;
    bool checkIsTakableInvert(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    bool checkfiveWin(unsigned int x, unsigned int y);
    bool checkFivePrize(unsigned int x, unsigned int y);
    unsigned int checkFivePrize(unsigned int x, unsigned int y, Vector dir, unsigned int player);

    /*
     * Fonction pour la prise de pierre
     */
    unsigned int checkPrize(unsigned int x, unsigned int y, const unsigned int player);
    bool checkPrize(unsigned int x, unsigned int y, Vector dir, unsigned int player) const;
    bool checkCanTake(unsigned x, unsigned int y, Vector dir, unsigned int player) const;
    void cleanRock(unsigned int x, unsigned int y, Vector dir, unsigned int player);

    /*
     * Fonction de propagation
     */

    void fpropagation(unsigned int x, unsigned int y, const unsigned int player);
    void fpropagation(unsigned int x, unsigned int y, Vector dir, const unsigned int player);
    void fpropagation_inverse(unsigned int x, unsigned int y, const unsigned int player);
    void fpropag_inverse_to(unsigned int x, unsigned int y, Vector dir, const unsigned int player);
    PropagationInfo flineSize(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    void fsetline(unsigned int x, unsigned int y, Vector dir, unsigned int player, const PropagationInfo& value);
    void resetTakable(unsigned int x, unsigned int y, Vector dir, unsigned int player, bool takable);

    /**
     * Fonction de Debug
     */

    void dumpSquare(unsigned int x, unsigned int y) const;
    void dumpDirection(unsigned int x, unsigned int y, Vector dir) const;
    void dumpPropagation(unsigned int x, unsigned int y) const;

};

#endif	/* REFEREE_HPP */

