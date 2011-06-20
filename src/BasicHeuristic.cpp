
#include <iostream>

#include "BasicHeuristic.hpp"
#include "Board.hpp"

BasicHeuristic::HeuristicValue BasicHeuristic::operator()(Board& gameBoard, unsigned int player, unsigned int x, unsigned int y) {
    int result = 0;
    int playerPiece = 0;
    int opponantPiece = 0;

    for (unsigned int x = 0; x < gameBoard.getSize(); ++x) {
        for (unsigned int y = 0; y < gameBoard.getSize(); ++y) {
            Square::Data& value = gameBoard(x, y).getData();
            if (value.player == player) {
                playerPiece++;
                if (value.is_takable)
                       result--;
            } else if (value.player != 0) {
                opponantPiece++;
                if (value.is_takable)
                    result++;
            }
        }
    }

    int diffPiece = playerPiece - opponantPiece;
    if (diffPiece < 0)
        diffPiece = diffPiece * diffPiece * -1;
    else
        diffPiece = diffPiece * diffPiece;

    result += diffPiece;
    //std::cout << "heu " << result << std::endl;
    return result;
}

int BasicHeuristic::good(Square::Data& square) {
    int result = 0;

    result += square.diagl * square.diagl;
    result += square.diagr * square.diagl;
    result += square.horz * square.diagl;
    result += square.vert * square.diagl;

    if (square.is_takable) {
        result *= -1;
    }

    return result;
}

int BasicHeuristic::bad(Square::Data& square) {
    int result = 0;

    result -= square.diagl;
    result -= square.diagr;
    result -= square.horz;
    result -= square.vert;

    return result;
}
