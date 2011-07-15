#ifndef THREEALIGNCHECKER_HPP
#define THREEALIGNCHECKER_HPP

class Board;

#include "RefereeManager.hpp"
#include "Array.hpp"

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
    Array<Coord, 2> _coord;
    std::size_t _size;

    unsigned int getAlignOf(Array<Coord, 2> square, unsigned int player, Vector dir);

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

    inline bool edgeTest(unsigned int x, unsigned int y, unsigned int /*player*/, Vector dir) {
        return goTo(x, y, dir) && getPlayer(x, y) == 0;
    }
    inline bool setCoord(unsigned int index, unsigned int x, unsigned int y) {
        _coord[index] = Coord(x, y);
        return true;
    }


};

unsigned int ThreeAlignChecker::ClassicEdge(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) {

    if (edgeTest(x, y, player, invert(dir)) &&
            goTo(x, y, dir) && getPlayer(x, y) == player && setCoord(0, x, y) &&
            goTo(x, y, dir) && getPlayer(x, y) == player && setCoord(1, x, y) &&
            edgeTest(x, y, player, dir)) {
        return 1;
    }
    return 0;
}

unsigned int ThreeAlignChecker::ClassicCenter(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    unsigned int xtmp = x;
    unsigned int ytmp = y;

    if (goTo(xtmp, ytmp, invert(dir)) && getPlayer(xtmp, ytmp) == player && setCoord(0, xtmp, ytmp) &&
            edgeTest(xtmp, ytmp, player, invert(dir)) &&
            goTo(x, y, dir) && getPlayer(x, y) == player && setCoord(1, x, y) &&
            edgeTest(x, y, player, dir)) {
        return 1;
    }
    return 0;
}

unsigned int ThreeAlignChecker::unClassicEdge_1(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    if (edgeTest(x, y, player, invert(dir)) &&
            goTo(x, y, dir) && getPlayer(x, y) == player && setCoord(0, x, y) &&
            goTo(x, y, dir) && getPlayer(x, y) == 0 &&
            goTo(x, y, dir) && getPlayer(x, y) == player && setCoord(1, x, y) &&
            edgeTest(x, y, player, dir)) {
        return 1;
    }
    return 0;
}

unsigned int ThreeAlignChecker::unClassicEdge_2(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    if (edgeTest(x, y, player, invert(dir)) &&
            goTo(x , y, dir) && getPlayer(x, y) == 0 &&
            goTo(x, y, dir) && getPlayer(x, y) == player && setCoord(0, x, y) &&
            goTo(x, y, dir) && getPlayer(x, y) == player && setCoord(1, x, y) &&
            edgeTest(x, y, player, dir)) {
        return 1;
    }
    return 0;
}

unsigned int ThreeAlignChecker::unClassicCenter(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    unsigned int xtmp = x;
    unsigned int ytmp = y;

    if (goTo(xtmp, ytmp, invert(dir)) && getPlayer(xtmp, ytmp) == player && setCoord(0, xtmp, ytmp) &&
            edgeTest(xtmp, ytmp, player, invert(dir)) &&
            goTo(x, y, dir) && getPlayer(x, y) == 0 &&
            goTo(x, y, dir) && getPlayer(x, y) == player && setCoord(1, x, y) &&
            edgeTest(x, y, player, dir)) {
        return 1;
    }
    return 0;
}

#endif // THREEALIGNCHECKER_HPP
