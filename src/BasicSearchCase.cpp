
#include "BasicSearchCase.hpp"

void BasicSearchCase::operator ()(Board& game, CoordContainer& possibleCase) {
    unsigned int size = game.getSize();

    for (unsigned int x = 0; x < size; ++x) {
        for (unsigned int y = 0; y < size; ++y) {
            if (game(x, y).getData().player == 0) {
                possibleCase.push_back(Coord(x, y));
            }
        }
    }
}
