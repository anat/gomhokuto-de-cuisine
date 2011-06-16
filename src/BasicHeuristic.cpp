
#include "BasicHeuristic.hpp"
#include "Board.hpp"

typename BasicHeuristic::HeuristicValue BasicHeuristic::operator()(Board& gameBoard, unsigned int player) {
    int result = 0;

    for (unsigned int x = 0; x < gameBoard.getSize(); ++x) {
        for (unsigned int y = 0; y < gameBoard.getSize(); ++y) {
            Square::Data& value = gameBoard(x, y).getData();
            if (value.player == player) {
                result += good(value);
            }
            if (value.player != 0 && value.player != player) {
                result += bad(value);
            }
        }
    }
    return result;
}

int BasicHeuristic::good(Square::Data& square) {
    int result = 0;
    
    if (!square.is_takable)
        result += 2;
    result += square.diagl;
    result += square.diagr;
    result += square.horz;
    result += square.vert;

    return result;
}

int BasicHeuristic::bad(Square::Data& square) {
    int result = 0;
    
    if (square.is_takable) {
        result += 1;
    }

    result -= square.diagl;
    result -= square.diagr;
    result -= square.horz;
    result -= square.vert;

    return result;
}
