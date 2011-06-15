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

#define DIR_UP    0x1
#define DIR_DOWN  0x2
#define DIR_LEFT  0x4
#define DIR_RIGHT 0x8

/**
 * L'arbitre
 */

class Referee {
public:
    Referee(Board& board);
    Referee(const Referee& orig);
    virtual ~Referee();

    int tryPlaceRock(unsigned int x, unsigned int y, unsigned int player); //Test et si ok place
    bool testPosition(unsigned int x, unsigned int y, unsigned int player); //Test tout cours
    unsigned int checkWin() const;
    bool doubleThree() const;
    bool fivePrize() const;
    bool doubleThree(bool value);
    bool fivePrize(bool value);
    void reset();

private:
    typedef std::list<Coord> WinList;

    Board& _board;
    unsigned int _winner;
    WinList _winLineList;

    inline unsigned int opponant(const unsigned int pla) const {
        unsigned int result = 0;
        if (pla == 1)
            result = 2;
        else if (pla == 2)
            result = 1;
        return result;
    }

    inline bool checkPosition(unsigned int x, unsigned int y) const {
        return (x < _board.getSize() && y < _board.getSize());
    }

    inline unsigned int abs(int value) const {
        if (value < 0)
            return value * -1;
        return value;
    }

    inline RefereeManager::Vector invert(RefereeManager::Vector dir) const {
        RefereeManager::DirMap::const_iterator it = Singleton<RefereeManager>::Instance().find(dir);

        if (it != Singleton<RefereeManager>::Instance().end())
            return it->second.invert;
        return RefereeManager::NONE;
    }

    bool goTo(unsigned int& x, unsigned int& y, RefereeManager::Vector dir) const;
    unsigned int getDirAlign(const Square& value, RefereeManager::Vector dir) const;
    void setDirAlign(Square& square, RefereeManager::Vector dir, unsigned int value);
    bool ispartOfAlign(const Square& value, int size);
    bool ispartOfExactAlign(const Square& value, int size);
    void setTakable(Square& square, bool value) {
        square.getData().is_takable = value;
    }

    /*
     * Fonction de check pour les double alignement de trois
     */
    bool checkDoubleThree(unsigned int x, unsigned int y, unsigned int player);
    unsigned int isPartOfFree3Align(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player);
    unsigned int classicFree3Align(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player);
    unsigned int unClassicFree3Align(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player);
    unsigned int isPartOfAlign3InOther(unsigned x, unsigned int y, RefereeManager::Vector dir, unsigned int player);
    bool isFreeAlign(unsigned int x, unsigned int y, RefereeManager::Vector dirorig, RefereeManager::Vector dir, unsigned int player);

    /*
     * Fonction pour la victoire par alignement de 5
     */
    void checkWin(unsigned int x, unsigned int y);
    void checkWinList();
    void checkIsTakable(unsigned int x, unsigned int y, unsigned int player);
    bool checkIsTakable(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) const;
    bool checkIsTakableInvert(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player);
    bool checkfiveWin(unsigned int x, unsigned int y);
    bool checkFivePrize(unsigned int x, unsigned int y);
    unsigned int checkFivePrize(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player);

    /*
     * Fonction pour la prise de pierre
     */
    unsigned int checkPrize(unsigned int x, unsigned int y, const unsigned int player);
    bool checkPrize(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) const;
    bool checkCanTake(unsigned x, unsigned int y, RefereeManager::Vector dir, unsigned int player) const;
    void cleanRock(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player);

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
    void fpropagation(unsigned int x, unsigned int y, RefereeManager::Vector dir, const unsigned int player);
    void fpropagation_inverse(unsigned int x, unsigned int y, const unsigned int player);
    void fpropag_inverse_to(unsigned int x, unsigned int y, RefereeManager::Vector dir, const unsigned int player);
    std::size_t flineSize(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player);
    void fsetline(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player, unsigned int value);
    void resetTakable(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player, bool takable);

    /**
     * Fonction de Debug
     */

    void dumpSquare(unsigned int x, unsigned int y) const;
    void dumpDirection(unsigned int x, unsigned int y, RefereeManager::Vector dir) const;
    void dumpPropagation(unsigned int x, unsigned int y) const;

};

#endif	/* REFEREE_HPP */

