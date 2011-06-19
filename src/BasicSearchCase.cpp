
#include <iostream>
#include "BasicSearchCase.hpp"

void BasicSearchCase::operator ()(Board& game, CoordContainer& possibleCase) {
    unsigned int size = game.getSize();

    for (unsigned int x = 0; x < size; ++x) {
        for (unsigned int y = 0; y < size; ++y) {
            if (game(x, y).getData().player == 0 && hasPlayerAround(game, x, y)) {
                possibleCase.push_back(Coord(x, y));
            }
        }
    }
    //Dump(possibleCase);
}

bool BasicSearchCase::hasPlayerAround(Board &game, unsigned int x, unsigned int y){
    unsigned int xtmp;
    unsigned int ytmp;
    bool ok = false;

    for (int xv = -1; xv < 2 && !ok; ++xv)
    {
        for (int yv = -1; yv < 2 && !ok; ++yv)
        {
            xtmp = x;
            ytmp = y;
            xtmp += xv;
            ytmp += yv;
            if (game.checkSize(xtmp, ytmp))
                ok = (game(xtmp, ytmp).getData().player != 0);
        }
    }
    return ok;
}

void BasicSearchCase::Dump(const CoordContainer & cont) const {
    CoordContainer::const_iterator it = cont.begin();
    CoordContainer::const_iterator ite = cont.end();


    std::cout << "##dump " << std::endl;
    while (it != ite)
    {
        std::cout << "x " << it->x << " y " << it->y << std::endl;
        ++it;
    }
}
