#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include <vector>
#include <set>

#include <boost/thread.hpp>
#include <boost/foreach.hpp>

#include "Board.hpp"
#include "APlayer.hpp"
#include "MinMax.hpp"

template < typename IHeuristic, typename ISearchCase >
class PlayerAi : public APlayer {
public:
    typedef typename IHeuristic::HeuristicValue HeuristicValue;
    typedef typename ISearchCase::CoordContainer CoordContainer;
    typedef std::pair< HeuristicValue, Coord > ResultPair;

    enum {
        DEPTH = 2,
        SIMUL_THREAD = 16
    };

    PlayerAi(unsigned int id) : APlayer(id), _heuristic(), _searchCase(), _sizeCoord(8) {
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
        }
        return *this;
    }

    bool doAction(Board& gameboard, Referee& referee, int, int) {
        timeval start;
        timeval end;
        gettimeofday(&start, NULL);

        CoordContainer possibleCase;
        std::vector< ResultPair > heuResult;

        _searchCase(gameboard, possibleCase);

        if (_sizeCoord < possibleCase.size())
            _sizeCoord = possibleCase.size();

        typename CoordContainer::iterator it = possibleCase.begin();
        typename CoordContainer::iterator ite = possibleCase.end();

        heuResult.resize(possibleCase.size());

        HeuristicValue BestHeu = _heuristic.defeat(0);
        Coord bestMove;

        unsigned int i = 0;
        std::cout << "depth max " << DEPTH << std::endl;
        std::cout << "base coord " << heuResult.size() << std::endl;
        boost::thread_group threadGroup;

        while (it != ite) {

            for (unsigned int u = 0; u < SIMUL_THREAD && it != ite; ++u) {
                heuResult[i].second = *it;

                threadGroup.create_thread(boost::bind(
                        &PlayerAi::explore_ab, this,
                        gameboard,
                        boost::ref(referee),
                        heuResult[i].second,
                        &heuResult[i].first
                        ));

                ++i;
                ++it;
            }

            threadGroup.join_all();
        }

        BOOST_FOREACH(ResultPair& value, heuResult) {
            if (value.first >= BestHeu) {
                BestHeu = value.first;
                bestMove = value.second;
            }
        }

        referee.tryPlaceRock(bestMove.x, bestMove.y, _player);

        gettimeofday(&end, NULL);
        timeval diff;
        diff.tv_sec = end.tv_sec - start.tv_sec;
        diff.tv_usec = end.tv_usec - start.tv_usec;
        if (diff.tv_usec < 0) {
            diff.tv_sec--;
            diff.tv_usec = 1000000 + diff.tv_usec;
        }
        std::cout << "perf " << diff.tv_sec << " " << diff.tv_usec << std::endl;
        return true;
    }

    void explore(Board& gameBoard, Referee& ref, Coord& pos, HeuristicValue* result) {
        Referee refcopy(ref, gameBoard);

        if (refcopy.tryPlaceRock(pos.x, pos.y, _player) > -1) {
            *result = min(DEPTH, refcopy);
        } else {
            *result = _heuristic.defeat(0);
        }
    }

    void explore_ab(Board& gameBoard, Referee& ref, Coord& pos, HeuristicValue* result) {
//        Referee refcopy(ref, gameBoard);
//
//        if (refcopy.tryPlaceRock(pos.x, pos.y, _player) > -1) {
//            *result = min_ab(DEPTH, refcopy, _heuristic.defeat(0), _heuristic.victory(0));
//        } else {
//            *result = _heuristic.defeat(0);
//        }
        MinMax< IHeuristic, ISearchCase, DEPTH> func(_player, gameBoard, ref, pos, result);
        func.run();
    }

    HeuristicValue min_ab(unsigned int depth, Referee& reforigin, HeuristicValue alpha, HeuristicValue beta) {
        if (!depth || reforigin.checkWin()) {
            unsigned int winner = reforigin.checkWin();
            if (winner == _player)
                return _heuristic.victory(depth);
            else if (winner)
                return _heuristic.defeat(depth);
            return _heuristic(reforigin.getBoard(), _player, depth);
        }

        CoordContainer possibleCase;

        //      possibleCase.reserve(_sizeCoord);
        _searchCase(reforigin.getBoard(), possibleCase);

        HeuristicValue heuResult;
        Board copy;

        BOOST_FOREACH(Coord& pos, possibleCase) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(pos.x, pos.y, Referee::opponant(_player)) > -1) {
                heuResult = max_ab(depth - 1, refcopy, alpha, beta);
                if (heuResult <= alpha) {
                    return alpha;
                }
                if (heuResult < beta) {
                    beta = heuResult;
                }
            }
        }

        return beta;
    }

    HeuristicValue max_ab(unsigned int depth, Referee& reforigin, HeuristicValue alpha, HeuristicValue beta) {
        if (!depth || reforigin.checkWin()) {
            unsigned int winner = reforigin.checkWin();
            if (winner == this->getPlayerNum())
                return _heuristic.victory(depth);
            else if (winner)
                return _heuristic.defeat(depth);
            return _heuristic(reforigin.getBoard(), _player, depth);
        }

        CoordContainer possibleCase;

        //    possibleCase.reserve(_sizeCoord);
        _searchCase(reforigin.getBoard(), possibleCase);

        HeuristicValue heuResult;
        Board copy;

        BOOST_FOREACH(Coord& pos, possibleCase) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(pos.x, pos.y, _player) > -1) {
                heuResult = min_ab(depth - 1, refcopy, alpha, beta);
                if (heuResult >= beta) {
                    return beta;
                }
                if (heuResult > alpha) {
                    alpha = heuResult;
                }
            }
        }

        return alpha;
    }

    HeuristicValue min(unsigned int depth, Referee& reforigin) {
        if (!depth || reforigin.checkWin()) {
            unsigned int winner = reforigin.checkWin();
            if (winner == _player)
                return _heuristic.victory(depth);
            else if (winner)
                return _heuristic.defeat(depth);
            return _heuristic(reforigin.getBoard(), _player, depth);
        }

        CoordContainer possibleCase;

        //  possibleCase.reserve(_sizeCoord);
        _searchCase(reforigin.getBoard(), possibleCase);

        HeuristicValue heuResult;
        HeuristicValue result = _heuristic.victory(depth);
        Board copy;

        BOOST_FOREACH(Coord& pos, possibleCase) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(pos.x, pos.y, Referee::opponant(_player)) > -1) {
                heuResult = max(depth - 1, refcopy);
                if (heuResult < result)
                    result = heuResult;
            }
        }

        return result;
    }

    HeuristicValue max(unsigned int depth, Referee& reforigin) {
        if (!depth || reforigin.checkWin()) {
            unsigned int winner = reforigin.checkWin();
            if (winner == this->getPlayerNum())
                return _heuristic.victory(depth);
            else if (winner)
                return _heuristic.defeat(depth);
            return _heuristic(reforigin.getBoard(), _player, depth);
        }

        CoordContainer possibleCase;

        //possibleCase.reserve(_sizeCoord);
        _searchCase(reforigin.getBoard(), possibleCase);

        HeuristicValue heuResult;
        HeuristicValue result = _heuristic.defeat(depth);
        Board copy;

        BOOST_FOREACH(Coord& pos, possibleCase) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(pos.x, pos.y, _player) > -1) {
                heuResult = min(depth - 1, refcopy);
                if (heuResult > result)
                    result = heuResult;
            }
        }

        return result;
    }

private:
    IHeuristic _heuristic;
    ISearchCase _searchCase;
    unsigned int _sizeCoord;
};

#endif // PLAYERAI_HPP
