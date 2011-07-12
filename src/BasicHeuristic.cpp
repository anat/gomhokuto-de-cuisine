
#include <iostream>

#include "BasicHeuristic.hpp"
#include "Board.hpp"

BasicHeuristic::HeuristicValue BasicHeuristic::operator()(Board& gameBoard, unsigned int player) {
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
                result += bad(value);
                opponantPiece++;
            }
        }
    }

    int test;
    if (playerPiece && opponantPiece) {
        float div = (float)playerPiece / (float)opponantPiece;
        test = result * div;
    }

    //std::cout << "heu " << result << std::endl;
    return test;
}

int BasicHeuristic::good(Square::Data& square) {
    int result = 0;

    result += square.diagl_block * square.diagl;
    result += square.diagr_block * square.diagr;
    result += square.horz_block * square.horz;
    result += square.vert_block * square.vert;

    if (square.is_takable) {
        result /= 2;
    }

    return result;
}

int BasicHeuristic::bad(Square::Data& square) {
    int result = 0;

    result += square.diagl_block * square.diagl;
    result += square.diagr_block * square.diagr;
    result += square.horz_block * square.horz;
    result += square.vert_block * square.vert;

    if (square.is_takable) {
        result /= 2;
    }

    return result * -1;
}

BasicHeuristic::HeuristicValue BasicHeuristic::victory() const {
    return 4000000;
}

BasicHeuristic::HeuristicValue BasicHeuristic::defeat() const {
    return -4000000;
}
