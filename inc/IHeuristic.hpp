#ifndef IHEURISTIC_HPP
#define IHEURISTIC_HPP

class Board;

template <typename Value>
class IHeuristic
{
public:
    typedef Value HeuristicValue;

    virtual ~IHeuristic() {}

    virtual HeuristicValue getHeuristic(Board& gameBoard, unsigned int player) = 0;
};

#endif // IHEURISTIC_HPP
