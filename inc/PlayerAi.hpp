#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include <vector>
#include <set>

#include "Board.hpp"
#include "APlayer.hpp"

template < typename IHeuristic, typename ISearchCase >
class PlayerAi : public APlayer {
public:
    typedef typename IHeuristic::HeuristicValue HeuristicValue;
    typedef typename ISearchCase::CoordContainer CoordContainer;

    PlayerAi(unsigned int id) : APlayer(id), _heuristic(), _maxDepth(3), _alpha(), _beta() {
    }

    PlayerAi(const PlayerAi& orig) : APlayer(orig) {
        this->operator =(orig);
    }

    ~PlayerAi() {
    }

    PlayerAi & operator=(const PlayerAi& orig) {
        if (this != &orig) {
            _heuristic = orig._heuristic;
            _maxDepth = orig._maxDepth;
            _alpha = orig._alpha;
            _beta = orig._beta;
        }
        return *this;
    }

    bool doAction(Board& gameboard, Referee& ref, int , int ) {
        _alpha = HeuristicValue();
        _beta = HeuristicValue();

        CoordContainer possibleCase;

        _searchCase(gameboard, possibleCase);

        typename CoordContainer::iterator it = possibleCase.begin();
        typename CoordContainer::iterator ite = possibleCase.end();

        Board copy;

        HeuristicValue BestHeu = HeuristicValue();
        Coord bestMove;

        while (it != ite) {
            copy = gameboard;
            Referee refcopy(ref, copy);
            if (refcopy.tryPlaceRock(it->x, it->y, this->getPlayerNum()) > -1) {
                HeuristicValue heu = min(1, copy, refcopy, _heuristic(copy, this->getPlayerNum(), it->x, it->y));

                if (heu >= BestHeu) {
                    heu = BestHeu;
                    bestMove = *it;
                }
            }
            ++it;
        }

        std::cout << "bestHeu " << BestHeu << std::endl;
        ref.tryPlaceRock(bestMove.x, bestMove.y, this->getPlayerNum());
        return true;
    }

    HeuristicValue min(unsigned int depth, Board& origin, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth > _maxDepth || reforigin.checkWin() != 0)
            return boardHeuristic;

        CoordContainer possibleCase;

        _searchCase(origin, possibleCase);

        typename CoordContainer::const_iterator it = possibleCase.begin();
        typename CoordContainer::const_iterator ite = possibleCase.end();

        HeuristicValue heuResult = HeuristicValue();
        HeuristicValue result = HeuristicValue();
        Board copy;

        while (it != ite) {
            copy = origin;
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(it->x, it->y, reforigin.opponant(this->getPlayerNum())) > -1) {
                heuResult = max(depth + 1, copy, refcopy, _heuristic(copy, this->getPlayerNum(), it->x, it->y));
                if (heuResult < result)
                    result = heuResult;
            }
            ++it;
        }

        return result;
    }

    HeuristicValue max(unsigned int depth, Board& origin, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth > _maxDepth || reforigin.checkWin() != 0) {
            return boardHeuristic;
        }

        CoordContainer possibleCase;

        _searchCase(origin, possibleCase);

        typename CoordContainer::const_iterator it = possibleCase.begin();
        typename CoordContainer::const_iterator ite = possibleCase.end();

        HeuristicValue heuResult = HeuristicValue();
        HeuristicValue result = HeuristicValue();
        Board copy;

        while (it != ite) {
            copy = origin;
            Referee refcopy(reforigin);

            if (refcopy.tryPlaceRock(it->x, it->y, this->getPlayerNum()) > -1) {
                heuResult = min(depth + 1, copy, refcopy, _heuristic(copy, this->getPlayerNum(), it->x, it->y));
                if (heuResult > result)
                    result = heuResult;
            }
            ++it;
        }

        return result;
    }

private:
    IHeuristic _heuristic;
    ISearchCase _searchCase;
    unsigned int _maxDepth;
    HeuristicValue _alpha;
    HeuristicValue _beta;
};

#endif // PLAYERAI_HPP
