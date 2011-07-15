#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include <vector>
#include <set>

#include <boost/thread.hpp>

#include "Board.hpp"
#include "APlayer.hpp"

template < typename IHeuristic, typename ISearchCase >
class PlayerAi : public APlayer {
public:
    typedef typename IHeuristic::HeuristicValue HeuristicValue;
    typedef typename ISearchCase::CoordContainer CoordContainer;

    PlayerAi(unsigned int id) : APlayer(id), _heuristic(), _searchCase(), _maxDepth(3), _alpha(), _beta() {
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

    bool doAction(Board& gameboard, Referee& ref, int, int) {
        CoordContainer possibleCase;
        std::vector< std::pair< HeuristicValue, Coord > > heuResult;

        _searchCase(gameboard, possibleCase);

        typename CoordContainer::iterator it = possibleCase.begin();
        typename CoordContainer::iterator ite = possibleCase.end();

        heuResult.resize(possibleCase.size());
        Board copy;
        //HeuristicValue heu;
        HeuristicValue BestHeu = _heuristic.defeat();
        Coord bestMove;

        _alpha = _heuristic.defeat();
        _beta = _heuristic.victory();
        unsigned int i = 0;
        boost::thread_group threadGroup;

        while (it != ite) {
            heuResult[i].second = *it;
            threadGroup.create_thread(
                    boost::bind(
                        &PlayerAi::explore, this,
                        boost::ref(gameboard),
                        boost::ref(ref),
                        heuResult[i].second,
                        boost::ref(heuResult[i].first)
                        )
                    );

            //            copy = gameboard;
            //            Referee refcopy(ref, copy);
            //
            //            if (refcopy.tryPlaceRock(it->x, it->y, _player) > -1) {
            //                heu = min(1, refcopy, _heuristic(copy, _player));
            //                if (heu >= BestHeu) {
            //                    BestHeu = heu;
            //                    bestMove = *it;
            //                }
            //            }

            ++i;
            ++it;
        }

        threadGroup.join_all();

        for (unsigned int i = 0; i < heuResult.size(); ++i) {
            if (heuResult[i].first >= BestHeu) {
                BestHeu = heuResult[i].first;
                bestMove = heuResult[i].second;
            }
        }

        ref.tryPlaceRock(bestMove.x, bestMove.y, _player);
        return true;
    }

    void explore(Board& gameBoard, Referee& ref, Coord& pos, HeuristicValue& result) {
        Board copy = gameBoard;
        Referee refcopy(ref, copy);

        //std::cout << "### x" << pos.x << " y " << pos.y << std::endl;
        if (refcopy.tryPlaceRock(pos.x, pos.y, _player) > -1) {
            result = min(1, refcopy, _heuristic(copy, _player));
        } else {
            result = _heuristic.defeat();
        }
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
                _betaMut.lock();
                if (heuResult < _beta)
                    _beta = heuResult;
                _betaMut.unlock();
                if (heuResult < result)
                    result = heuResult;
                _alphaMut.lock();
                _betaMut.lock();
                if (_beta < _alpha)
                    bad = true;
                _alphaMut.unlock();
                _betaMut.unlock();
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
                _alphaMut.lock();
                if (heuResult > _alpha)
                    _alpha = heuResult;
                _alphaMut.unlock();
                if (heuResult > result)
                    result = heuResult;
                _alphaMut.lock();
                _betaMut.lock();
                if (_beta > _alpha)
                    bad = true;
                _alphaMut.unlock();
                _betaMut.unlock();
            }
            ++it;
        }

        return result;
    }

private:
    IHeuristic _heuristic;
    ISearchCase _searchCase;
    const unsigned int _maxDepth;
    HeuristicValue _alpha;
    HeuristicValue _beta;
    boost::mutex _alphaMut;
    boost::mutex _betaMut;
};

#endif // PLAYERAI_HPP
