#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include <vector>
#include <set>

#include "Board.hpp"
#include "APlayer.hpp"

template < typename IHeuristic >
class PlayerAi : public APlayer {
public:
    typedef typename IHeuristic::HeuristicValue HeuristicValue;
    typedef std::vector<Coord> CoordContainer;
    typedef typename std::map< HeuristicValue, Coord > FinalContainer;

    PlayerAi(unsigned int id) : APlayer(id), _heuristic(), _maxDepth(3) {
    }

    PlayerAi(const PlayerAi& orig) {
        this->operator =(orig);
    }

    ~PlayerAi() {
    }

    PlayerAi & operator=(const PlayerAi& orig) {
        if (this != &orig) {
            _heuristic = orig._heuristic;
        }
        return *this;
    }

    bool doAction(Board& gameboard, Referee& ref, int , int ) {
        HeuristicValue originValue = _heuristic(gameboard, this->getPlayerNum());

        CoordContainer possibleCase;

        searchCase(gameboard, possibleCase);

        CoordContainer::iterator it = possibleCase.begin();
        CoordContainer::iterator ite = possibleCase.end();
        FinalContainer finalContainer;

        while (it != ite) {
            Board copy(gameboard);
            Referee refcopy(ref, copy);
            if (refcopy.tryPlaceRock(it->x, it->y, this->getPlayerNum()) > -1) {
                HeuristicValue heucopy = _heuristic(copy, this->getPlayerNum());
                if (heucopy > originValue) {
                    finalContainer[min(1, copy, refcopy, heucopy)] = *it;
                }
            }
            ++it;
        }

        typename FinalContainer::reverse_iterator final = finalContainer.rbegin();

        if (final != finalContainer.rend()) {
            ref.tryPlaceRock(final->second.x, final->second.y, this->getPlayerNum());
        }

        return true;
    }

    HeuristicValue min(unsigned int depth, Board& origin, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth > _maxDepth || reforigin.checkWin() != 0)
            return boardHeuristic;

        CoordContainer possibleCase;

        searchCase(origin, possibleCase);

        CoordContainer::iterator it = possibleCase.begin();
        CoordContainer::iterator ite = possibleCase.end();
        FinalContainer finalCoord;

        HeuristicValue result = HeuristicValue();

        Board copy;
        while (it != ite) {
            copy = origin;
            Referee refcopy(reforigin, copy);
            if (refcopy.tryPlaceRock(it->x, it->y, this->getPlayerNum()) > -1) {
                HeuristicValue heucopy = _heuristic(copy, this->getPlayerNum());
                if (heucopy < boardHeuristic) {
                    finalCoord[max(depth + 1, copy, refcopy, heucopy)] = *it;
                }
            }
            ++it;
        }

        typename FinalContainer::reverse_iterator final = finalCoord.rbegin();

        if (final != finalCoord.rend()) {
            result = final->first;
        }

        return result;
    }

    HeuristicValue max(unsigned int depth, Board& origin, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth > _maxDepth || reforigin.checkWin() != 0)
            return boardHeuristic;

        CoordContainer possibleCase;

        searchCase(origin, possibleCase);

        CoordContainer::iterator it = possibleCase.begin();
        CoordContainer::iterator ite = possibleCase.end();
        FinalContainer finalCoord;

        HeuristicValue result = HeuristicValue();

        while (it != ite) {
            Board copy(origin);
            Referee refcopy(reforigin);
            if (refcopy.tryPlaceRock(it->x, it->y, this->getPlayerNum()) > -1) {
                HeuristicValue heucopy = _heuristic(copy, this->getPlayerNum());
                if (heucopy > boardHeuristic) {
                    finalCoord[max(depth + 1, copy, refcopy, heucopy)] = *it;
                }
            }
            ++it;
        }

        typename FinalContainer::reverse_iterator final = finalCoord.rbegin();

        if (final != finalCoord.rend()) {
            result = final->first;
        }

        return result;
    }
private:
    IHeuristic _heuristic;
    unsigned int _maxDepth;

    void searchCase(Board& game, CoordContainer& possibleCase) {
        unsigned int size = game.getSize();
        for (unsigned int x = 0; x < size; ++x) {
            for (unsigned int y = 0; y < size; ++y) {
                if (game(x, y).getData().player == 0) {
                    possibleCase.push_back(Coord(x, y));
                }
            }
        }
    }
};

#endif // PLAYERAI_HPP
