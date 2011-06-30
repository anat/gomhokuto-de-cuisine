#ifndef IHEURISTIC_HPP
#define IHEURISTIC_HPP

class Board;

template <typename Value>
class IHeuristic
{
public:
    typedef Value HeuristicValue;

    virtual ~IHeuristic() {}

    // player : l'heuristic du plateau pour ce joueurs
    // x & y : le dernier coup jouer sur ce plateau
    virtual HeuristicValue operator()(Board& gameBoard, unsigned int player, unsigned int x, unsigned int y) = 0;
    virtual HeuristicValue victory() const = 0;
    virtual HeuristicValue defeat() const = 0;
};

#endif // IHEURISTIC_HPP
