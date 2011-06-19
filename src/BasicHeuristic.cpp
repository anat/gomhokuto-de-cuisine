
#include "BasicHeuristic.hpp"
#include "Board.hpp"

BasicHeuristic::HeuristicValue BasicHeuristic::operator()(Board& gameBoard, unsigned int player) {
    int result = 0;

    for (unsigned int x = 0; x < gameBoard.getSize(); ++x) {
        for (unsigned int y = 0; y < gameBoard.getSize(); ++y) {
            Square::Data& value = gameBoard(x, y).getData();
            if (value.player == player) {
                result += good(value);
            } else if (value.player != 0) {
                result -= good(value);
            }
        }
    }

    return result;
}

int BasicHeuristic::good(Square::Data& square) {
    int result = 0;

    if (!square.is_takable) {
        result += square.diagl * square.diagl;
        result += square.diagr * square.diagl;
        result += square.horz * square.diagl;
        result += square.vert * square.diagl;
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
