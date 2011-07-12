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

    PlayerAi(unsigned int id) : APlayer(id), _heuristic(), _searchCase(), _maxDepth(3), _alpha(_heuristic.defeat()), _beta(_heuristic.victory()) {
    }

    PlayerAi(const PlayerAi& orig) : APlayer(orig) {
        this->operator =(orig);
    }

    ~PlayerAi() {
    }

    PlayerAi & operator=(const PlayerAi& orig) {
        if (this != &orig) {
            _heuristic = orig._heuristic;
            _searchCase = orig._searchCase;
            _maxDepth = orig._maxDepth;
            _alpha = orig._alpha;
            _beta = orig._beta;
        }
        return *this;
    }

    bool doAction(Board& gameboard, Referee& ref, int , int ) {
        CoordContainer possibleCase;

        _searchCase(gameboard, possibleCase);

        typename CoordContainer::iterator it = possibleCase.begin();
        typename CoordContainer::iterator ite = possibleCase.end();

        Board copy;
        HeuristicValue heu;
        HeuristicValue BestHeu = _heuristic.defeat();
        Coord bestMove;

        while (it != ite) {
            copy = gameboard;
            Referee refcopy(ref, copy);

            if (refcopy.tryPlaceRock(it->x, it->y, _player) > -1) {
                heu = min(1, refcopy, _heuristic(copy, _player));
                if (heu > BestHeu) {
                    BestHeu = heu;
                    bestMove = *it;
                }
            }
            ++it;
        }

        ref.tryPlaceRock(bestMove.x, bestMove.y, this->getPlayerNum());
        return true;
    }

    HeuristicValue min(unsigned int depth, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth > _maxDepth || reforigin.checkWin() != 0) {
            unsigned int winner = reforigin.checkWin();
            if (winner == _player)
                return _heuristic.victory();
            else if (winner)
                return _heuristic.defeat();
            return boardHeuristic;
        }

        CoordContainer possibleCase;

        _searchCase(reforigin.getBoard(), possibleCase);

        typename CoordContainer::const_iterator it = possibleCase.begin();
        typename CoordContainer::const_iterator ite = possibleCase.end();

        HeuristicValue heuResult;
        HeuristicValue result = _heuristic.victory();
        Board copy;

        bool bad = false;
        while (it != ite && !bad) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(it->x, it->y, Referee::opponant(_player)) > -1) {
                heuResult = max(depth + 1, refcopy, _heuristic(copy, _player));
                if (heuResult < _beta)
                    _beta = heuResult;
                if (heuResult < result)
                    result = heuResult;
            }
            ++it;
        }

        return result;
    }

    HeuristicValue max(unsigned int depth, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth > _maxDepth || reforigin.checkWin() != 0) {
            unsigned int winner = reforigin.checkWin();
            if (winner == this->getPlayerNum())
                return _heuristic.victory();
            else if (winner)
                return _heuristic.defeat();
            return boardHeuristic;
        }

        CoordContainer possibleCase;

        _searchCase(reforigin.getBoard(), possibleCase);

        typename CoordContainer::const_iterator it = possibleCase.begin();
        typename CoordContainer::const_iterator ite = possibleCase.end();

        HeuristicValue heuResult;
        HeuristicValue result = _heuristic.defeat();
        Board copy;
        bool bad = false;

        while (it != ite && !bad) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(it->x, it->y, _player) > -1) {
                heuResult = min(depth + 1, refcopy, _heuristic(copy, _player));
                if (heuResult > _alpha)
                    _alpha = heuResult;
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
