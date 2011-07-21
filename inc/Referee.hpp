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

#include <boost/thread.hpp>

#include "Coord.hpp"
#include "RefereeManager.hpp"
#include "ThreeAlignChecker.hpp"

class Board;

/**
 * L'arbitre
 */

class Referee {
public:
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
    unsigned int getScore(unsigned int player) const;

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
    typedef RefereeManager::Vector Vector;
    typedef std::list<Coord> WinList;

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

    struct CheckPrizeInfo {
        unsigned int x;
        unsigned int y;
        Vector dir;
        unsigned int player;
        unsigned int result;
    };

    WinList _winLineList;
    Board& _board;
    ThreeAlignChecker _threeChecker;
    Array< unsigned int, 2 > _score;
    unsigned int _winner;
    mutable boost::mutex _squareMutex;

    void setScore(unsigned int player, unsigned int value);

    bool goTo(unsigned int& x, unsigned int& y, Vector dir) const;
    unsigned int getDirAlign(const Square& value, Vector dir) const;
    void setDirAlign(Square& square, Vector dir, unsigned int value);
    unsigned int getDirEnd(const Square& square, Vector dir) const;
    void setDirEnd(Square& square, Vector dir, unsigned int endValue);
    bool ispartOfAlign(const Square& value, unsigned int size);
    bool ispartOfExactAlign(const Square& value, int size);
    void setRaw(Square& value, unsigned int val);
    
    /*
     * Fonction de check pour les double alignement de trois
     */

    bool checkDoubleThree(unsigned int x, unsigned int y, unsigned int player);

    /*
     * Fonction pour la victoire par alignement de 5
     */
    void checkWin(unsigned int x, unsigned int y, unsigned int player);
    void checkWinList();
    bool checkIsTakable(unsigned int x, unsigned int y);
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
    void cleanRock(unsigned int x, unsigned int y, Vector dir);

    /*
     * Fonction de propagation
     */

    void fpropagation(unsigned int x, unsigned int y, const unsigned int player);
    void fpropagation_dir(unsigned int x, unsigned int y, Vector dir, const unsigned int player);
    void fpropagation_inverse(unsigned int x, unsigned int y);
    void fpropag_inverse_to(unsigned int x, unsigned int y, Vector dir);
    PropagationInfo flineSize(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    void fsetline(unsigned int x, unsigned int y, Vector dir, unsigned int player, const PropagationInfo& value);

    /**
     * Fonction de Debug
     */

    void dumpSquare(unsigned int x, unsigned int y) const;
    void dumpDirection(unsigned int x, unsigned int y, Vector dir) const;
    void dumpPropagation(unsigned int x, unsigned int y) const;

};

#endif	/* REFEREE_HPP */

