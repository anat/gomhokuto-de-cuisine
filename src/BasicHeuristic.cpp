
#include <iostream>

#include "BasicHeuristic.hpp"
#include "Board.hpp"

BasicHeuristic::HeuristicValue BasicHeuristic::operator()(Board& gameBoard, unsigned int player, unsigned int /*x*/, unsigned int /*y*/) {
    int result = 0;
    int playerPiece = 0;
    int opponantPiece = 0;

    for (unsigned int x = 0; x < gameBoard.getSize(); ++x) {
        for (unsigned int y = 0; y < gameBoard.getSize(); ++y) {
            Square::Data& value = gameBoard(x, y).getData();
            if (value.player == player) {
                result += good(value);
                playerPiece++;
            } else if (value.player != 0) {
                result -= good(value);
                opponantPiece++;
            }
        }
    }

    if (playerPiece && opponantPiece) {
        float div = playerPiece / opponantPiece;
        result = result * div * div;
    }

    //std::cout << "heu " << result << std::endl;
    return result;
}

int BasicHeuristic::good(Square::Data& square) {
    int result = 0;

    result += square.diagl * square.diagl / 2 * square.diagl_block;
    result += square.diagr * square.diagr / 2 * square.diagr_block;
    result += square.horz * square.horz / 2 * square.horz_block;
    result += square.vert * square.vert / 2 * square.vert_block;

    if (square.is_takable) {
        result /= 2;
    }

    return result;
}

int BasicHeuristic::bad(Square::Data& square) {
    int result = 0;

    result -= square.diagl * square.diagl * square.diagl_block * square.diagl_block * square.diagl_block;
    result -= square.diagr * square.diagr * square.diagr_block * square.diagr_block * square.diagr_block;
    result -= square.horz * square.horz * square.horz_block * square.horz_block * square.horz_block;
    result -= square.vert * square.vert * square.vert_block * square.vert_block * square.vert_block;

    if (square.is_takable) {
        result /= 2;
    }

    return result;
}

BasicHeuristic::HeuristicValue BasicHeuristic::victory() const {
    return 4000000;
}

BasicHeuristic::HeuristicValue BasicHeuristic::defeat() const {
    return -4000000;
}
