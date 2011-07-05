
#include "Board.hpp"
#include "ThreeAlignChecker.hpp"

ThreeAlignChecker::ThreeAlignChecker(Board& value) : _board(value), _size(value.getSize())
{ }

ThreeAlignChecker::ThreeAlignChecker(const ThreeAlignChecker& orig) : _board(orig._board), _size(orig._size)
{ }

ThreeAlignChecker::~ThreeAlignChecker()
{ }

ThreeAlignChecker& ThreeAlignChecker::operator=(const ThreeAlignChecker& orig) {
    if (this != &orig) {
        _size = orig._size;
    }
    return *this;
}

bool ThreeAlignChecker::CheckDoubleThree(unsigned int x, unsigned int y, unsigned int player) {
    return ThreeAlignValue(x, y, player) >= 2;
}

unsigned int ThreeAlignChecker::ThreeAlignValue(unsigned int x, unsigned int y, unsigned int player) {
    unsigned int result = 0;
    unsigned int size = RefereeManager::Instance().size();
    const RefereeManager::VectorArray& dir = RefereeManager::Instance().getVectorArray();

    for (unsigned int i = 1; i < size && result < 2; ++i)
    {
        if (ClassicEdge(x, y, dir[i], player))
            result += getAlignOf(_coord, player, dir[i]) + 1;
        if (unClassicEdge_1(x, y, dir[i], player))
            result += getAlignOf(_coord, player, dir[i]) + 1;
        if (unClassicEdge_2(x, y, dir[i], player))
            result += getAlignOf(_coord, player, dir[i]) + 1;
        if (unClassicCenter(x, y, dir[i], player))
            result += getAlignOf(_coord, player, dir[i]) + 1;
    }

    if (result < 2) {
        if (ClassicCenter(x, y, RefereeManager::DOWN, player))
            result += getAlignOf(_coord, player, RefereeManager::DOWN);

        result += ClassicCenter(x, y, RefereeManager::LEFT, player);
        result += ClassicCenter(x, y, RefereeManager::UP_RIGHT, player);
        result += ClassicCenter(x, y, RefereeManager::UP_LEFT, player);
    }

    return result;
}

unsigned int ThreeAlignChecker::ThreeAlignValue(unsigned int x, unsigned int y, unsigned int player, Vector ignoreDir) {
    Vector invert_ = invert(ignoreDir);
    unsigned int result = 0;
    unsigned int size = RefereeManager::Instance().size();

    for (unsigned int i = 1; i < size; ++i)
    {
        if (static_cast<Vector>(i) != ignoreDir && static_cast<Vector>(i) != invert_) {
            result += ClassicEdge(x, y, static_cast<Vector>(i), player);
            result += unClassicEdge_1(x, y, static_cast<Vector>(i), player);
            result += unClassicEdge_2(x, y, static_cast<Vector>(i), player);
            result += unClassicCenter(x, y, static_cast<Vector>(i), player);
        }
    }

    if (RefereeManager::DOWN != ignoreDir && RefereeManager::DOWN != invert_)
        result += ClassicCenter(x, y, RefereeManager::DOWN, player);

    if (RefereeManager::LEFT != ignoreDir && RefereeManager::LEFT != invert_)
        result += ClassicCenter(x, y, RefereeManager::LEFT, player);

    if (RefereeManager::UP_RIGHT != ignoreDir && RefereeManager::UP_RIGHT != invert_)
        result += ClassicCenter(x, y, RefereeManager::UP_RIGHT, player);

    if (RefereeManager::UP_LEFT != ignoreDir && RefereeManager::UP_LEFT != invert_)
        result += ClassicCenter(x, y, RefereeManager::UP_LEFT, player);

    return result;
}

unsigned int ThreeAlignChecker::getAlignOf(Array<Coord, 2> square, unsigned int player, Vector dir) {
    unsigned int result = ThreeAlignValue(square[0].x, square[0].y, player, dir);

    result += ThreeAlignValue(square[1].x, square[1].y, player, dir);
    return result;
}

