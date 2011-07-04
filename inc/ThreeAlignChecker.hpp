#ifndef THREEALIGNCHECKER_HPP
#define THREEALIGNCHECKER_HPP

class Board;

#include "RefereeManager.hpp"

class ThreeAlignChecker {
public:
    typedef RefereeManager::Vector Vector;

    ThreeAlignChecker(Board& value);
    ThreeAlignChecker(const ThreeAlignChecker& orig);
    ~ThreeAlignChecker();
    ThreeAlignChecker& operator=(const ThreeAlignChecker& orig);

    bool CheckDoubleThree(unsigned int x, unsigned int y, unsigned int player);
    unsigned int ThreeAlignValue(unsigned int x, unsigned int y, unsigned int player);
    unsigned int ThreeAlignValue(unsigned int x, unsigned int y, unsigned int player, Vector ignoreDir);

private:
    Board& _board;
    std::size_t _size;

    inline unsigned int ClassicEdge(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    inline unsigned int ClassicCenter(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    inline unsigned int unClassicEdge_1(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    inline unsigned int unClassicEdge_2(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    inline unsigned int unClassicCenter(unsigned int x, unsigned int y, Vector dir, unsigned int player);

    inline unsigned opponant(unsigned int player) {
        if (player == 1)
            return 2;
        else if (player == 2)
            return 1;
        return 0;
    }

    inline Vector invert(Vector dir) {
        return RefereeManager::Instance().invert(dir);
    }

    inline bool goTo(unsigned int& x, unsigned int& y, Vector dir) {
        return RefereeManager::Instance().goTo(_size, x, y, dir);
    }

    inline unsigned int getPlayer(unsigned int x, unsigned int y) {
        return _board(x, y).getPlayer();
    }

    inline bool edgeTest(unsigned int x, unsigned int y, unsigned int player, Vector dir) {
        return goTo(x, y, dir) && getPlayer(x, y) == 0;
    }
};

unsigned int ThreeAlignChecker::ClassicEdge(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) {

    if (edgeTest(x, y, player, invert(dir)) &&
            goTo(x, y, dir) && getPlayer(x, y) == player && goTo(x, y, dir) && getPlayer(x, y) == player &&
            edgeTest(x, y, player, dir)) {
        return 1;
    }
    return 0;
}

unsigned int ThreeAlignChecker::ClassicCenter(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    unsigned int xtmp = x;
    unsigned int ytmp = y;

    if (goTo(xtmp, ytmp, invert(dir)) && getPlayer(xtmp, ytmp) == player && edgeTest(xtmp, ytmp, player, invert(dir)) &&
        goTo(x, y, dir) && getPlayer(x, y) == player && edgeTest(x, y, player, dir)) {
        return 1;
    }
    return 0;
}

unsigned int ThreeAlignChecker::unClassicEdge_1(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    if (edgeTest(x, y, player, invert(dir)) &&
            goTo(x, y, dir) && getPlayer(x, y) == player &&
            goTo(x, y, dir) && getPlayer(x, y) == 0 &&
            goTo(x, y, dir) && getPlayer(x, y) == player &&
            edgeTest(x, y, player, dir)) {
        return 1;
    }
    return 0;
}

unsigned int ThreeAlignChecker::unClassicEdge_2(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    if (edgeTest(x, y, player, invert(dir)) &&
            goTo(x , y, dir) && getPlayer(x, y) == 0 &&
            goTo(x, y, dir) && getPlayer(x, y) == player &&
            goTo(x, y, dir) && getPlayer(x, y) == player &&
            edgeTest(x, y, player, dir)) {
        return 1;
    }
    return 0;
}

unsigned int ThreeAlignChecker::unClassicCenter(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    unsigned int xtmp = x;
    unsigned int ytmp = y;

    if (goTo(xtmp, ytmp, invert(dir)) && getPlayer(xtmp, ytmp) == player &&
            edgeTest(xtmp, ytmp, player, invert(dir)) &&
            goTo(x, y, dir) && getPlayer(x, y) == 0 &&
            goTo(x, y, dir) && getPlayer(x, y) == player &&
            edgeTest(x, y, player, dir)) {
        return 1;
    }
    return 0;
}

#endif // THREEALIGNCHECKER_HPP
