#ifndef IHEURISTIC_HPP
#define IHEURISTIC_HPP

class Board;

template <typename Value>
class IHeuristic
{
public:
    typedef Value HeuristicValue;

    virtual ~IHeuristic() {}

    virtual HeuristicValue operator()(Board& gameBoard, unsigned int player, unsigned int depth) = 0;
    virtual HeuristicValue victory(unsigned int depth) const = 0;
    virtual HeuristicValue defeat(unsigned int depth) const = 0;
};

#endif // IHEURISTIC_HPP
