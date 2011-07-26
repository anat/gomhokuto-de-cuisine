
#include <iostream>

#include "BasicHeuristic.hpp"
#include "Board.hpp"

BasicHeuristic::HeuristicValue BasicHeuristic::operator()(const Board& gameBoard, unsigned int player, unsigned int depth) {
    int result = 0;
    int playerPiece = 0;
    int opponantPiece = 0;

    for (unsigned int x = 0; x < gameBoard.getSize(); ++x) {
        for (unsigned int y = 0; y < gameBoard.getSize(); ++y) {
            const Square::Data& value = gameBoard(x, y).getData();
            if (value.player == player) {
                result += good(value);
                playerPiece++;
            } else if (value.player != 0) {
                result += bad(value);
                opponantPiece++;
            }
        }
    }

    result += playerPiece * 2;
    result -= opponantPiece * 2;

    return result;
}

int BasicHeuristic::good(const Square::Data& square) {
    int result = 0;

    result += square.diagl_block * square.diagl_block * square.diagl;
    result += square.diagr_block * square.diagr_block * square.diagr;
    result += square.horz_block * square.horz_block * square.horz;
    result += square.vert_block * square.vert_block * square.vert;


    if (!square.is_takable) {
        return result;
    }
    return result / 4;
}

int BasicHeuristic::bad(const Square::Data& square) {
    return good(square) * -1;
}

BasicHeuristic::HeuristicValue BasicHeuristic::victory(unsigned int depth) const {
    return 400000 + depth;
}

BasicHeuristic::HeuristicValue BasicHeuristic::defeat(unsigned int depth) const {
    return -400000 - depth;
}
