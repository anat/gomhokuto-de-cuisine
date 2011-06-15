#ifndef BASICHEURISTIC_HPP
#define BASICHEURISTIC_HPP

#include "IHeuristic.hpp"

class Board;

class BasicHeuristic : IHeuristic<int>
{
public:
    HeuristicValue getHeuristic(Board& gameBoard, unsigned int player);
};

#endif // BASICHEURISTIC_HPP
