#ifndef BASICHEURISTIC_HPP
#define BASICHEURISTIC_HPP

#include "IHeuristic.hpp"
#include "Square.hpp"

class Board;

class BasicHeuristic : public IHeuristic<int>
{
public:
    HeuristicValue operator()(const Board& gameBoard, unsigned int player, unsigned int depth);

    HeuristicValue victory(unsigned int depth) const;
    HeuristicValue defeat(unsigned int depth) const;

private:
    int good(const Square::Data& square);
    int bad(const Square::Data& square);
};

#endif // BASICHEURISTIC_HPP
