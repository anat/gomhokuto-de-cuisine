
#include <iostream>
#include "BasicSearchCase.hpp"

void BasicSearchCase::operator ()(const Board& game, CoordContainer& possibleCase) {
    unsigned int containerSize = 0;
    unsigned int size = game.getSize();

    for (unsigned int x = 0; x < size; ++x) {
        for (unsigned int y = 0; y < size; ++y) {
            if (game(x, y).getPlayer() == 0 && hasPlayerAround_double(game, x, y)) {
                possibleCase.push_back(Coord(x, y));
                containerSize++;
            }
        }
    }

    if (!containerSize) {
        for (unsigned int x = 0; x < size; ++x) {
            for (unsigned int y = 0; y < size; ++y) {
                if (game(x, y).getPlayer() == 0 && hasPlayerAround_simple(game, x, y)) {
                    possibleCase.push_back(Coord(x, y));
                    containerSize++;
                }
            }
        }
    }
    //Dump(possibleCase);
}

bool BasicSearchCase::hasPlayerAround_double(const Board &game, unsigned int x, unsigned int y) {
    unsigned int xtmp;
    unsigned int ytmp;
    unsigned int ok = 0;

    for (int xv = -1; xv < 2 && ok < 2; ++xv) {
        for (int yv = -1; yv < 2 && ok < 2; ++yv) {
            xtmp = x;
            ytmp = y;
            xtmp += xv;
            ytmp += yv;
            if (game.checkSize(xtmp, ytmp) && game(xtmp, ytmp).getPlayer())
                ok++;
        }
    }

    if (ok != 0) {
        for (int xv = -1; xv < 2 && ok < 2; ++xv) {
            for (int yv = -1; yv < 2 && ok < 2; ++yv) {
                xtmp = x;
                ytmp = y;
                xtmp += xv * 2;
                ytmp += yv * 2;
                if (game.checkSize(xtmp, ytmp) && game(xtmp, ytmp).getPlayer())
                    ok++;
            }
        }
    }

    return ok >= 2;
}

bool BasicSearchCase::hasPlayerAround_simple(const Board &game, unsigned int x, unsigned int y) {
    unsigned int xtmp;
    unsigned int ytmp;
    bool ok = false;

    for (int xv = -1; xv < 2 && !ok ; ++xv) {
        for (int yv = -1; yv < 2 && !ok ; ++yv) {
            xtmp = x;
            ytmp = y;
            xtmp += xv;
            ytmp += yv;
            if (game.checkSize(xtmp, ytmp) && game(xtmp, ytmp).getPlayer())
                ok = true;
        }
    }

    return ok;
}

void BasicSearchCase::Dump(const CoordContainer & cont) const {
    CoordContainer::const_iterator it = cont.begin();
    CoordContainer::const_iterator ite = cont.end();


    std::cout << "##dump " << std::endl;
    while (it != ite) {
        std::cout << "x " << it->x << " y " << it->y << std::endl;
        ++it;
    }
}
