#ifndef BASICHEURISTIC_HPP
#define BASICHEURISTIC_HPP

#include "IHeuristic.hpp"
#include "Square.hpp"

class Board;

class BasicHeuristic : public IHeuristic<int>
{
public:
    HeuristicValue operator()(Board& gameBoard, unsigned int player, unsigned int x, unsigned int y);

    HeuristicValue victory() const;
    HeuristicValue defeat() const;
private:
    int good(Square::Data& square);
    int bad(Square::Data& square);
};

#endif // BASICHEURISTIC_HPP
