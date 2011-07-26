#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include <vector>
#include <set>

#include <boost/thread.hpp>
#include <boost/foreach.hpp>

#include "Board.hpp"
#include "APlayer.hpp"

template < typename IHeuristic, typename ISearchCase >
class PlayerAi : public APlayer {
public:
    typedef typename IHeuristic::HeuristicValue HeuristicValue;
    typedef typename ISearchCase::CoordContainer CoordContainer;

    enum {
        DEPTH = 3,
        SIMUL_THREAD = 4
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

    bool doAction(Board& gameboard, Referee& ref, int, int) {
        CoordContainer possibleCase;
        std::vector< std::pair< HeuristicValue, Coord > > heuResult;

        possibleCase.reserve(_sizeCoord);

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
                        ref,
                        heuResult[i].second,
                        &heuResult[i].first
                        ));
                ++i;
                ++it;
            }

            threadGroup.join_all();
        }

        std::cout << "------------" << std::endl;
        std::cout << "heuResult " << heuResult.size() << std::endl;

        for (unsigned int o = 0; o < heuResult.size(); ++o) {
            std::cout << "heu " << heuResult[o].first << " pos ";
            heuResult[o].second.dump(std::cout);
            if (heuResult[o].first >= BestHeu) {
                BestHeu = heuResult[o].first;
                bestMove = heuResult[o].second;
            }
        }

        std::cout << "-------------" << std::endl;

        ref.tryPlaceRock(bestMove.x, bestMove.y, _player);
        return true;
    }

    void explore(Board& gameBoard, Referee& ref, Coord& pos, HeuristicValue* result) {
        //std::cout << "thread launch" << std::endl;
        Referee refcopy(ref, gameBoard);

        //std::cout << "### x" << pos.x << " y " << pos.y << std::endl;
        if (refcopy.tryPlaceRock(pos.x, pos.y, _player) > -1) {
            *result = min(1, refcopy, _heuristic(gameBoard, _player, 1));
        } else {
            *result = _heuristic.defeat(0);
        }
        //std::cout << "thread end : " << *result << std::endl;
    }

    void explore_ab(Board& gameBoard, Referee& ref, Coord& pos, HeuristicValue* result) {
        Referee refcopy(ref, gameBoard);

        std::cout << "### x" << pos.x << " y " << pos.y << std::endl;
        if (refcopy.tryPlaceRock(pos.x, pos.y, _player) > -1) {
            *result = min_ab(1, refcopy, _heuristic(gameBoard, _player, 1), _heuristic.defeat(0), _heuristic.victory(0));
        } else {
            *result = _heuristic.defeat(0);
        }
    }

    HeuristicValue min_ab(unsigned int depth, Referee& reforigin, HeuristicValue boardHeuristic, HeuristicValue alpha, HeuristicValue beta) {
        if (depth >= DEPTH || reforigin.checkWin() != 0) {
            unsigned int winner = reforigin.checkWin();
            if (winner == _player)
                return _heuristic.victory(depth);
            else if (winner)
                return _heuristic.defeat(depth);
            return boardHeuristic;
        }

        CoordContainer possibleCase;

        possibleCase.reserve(_sizeCoord);
        _searchCase(reforigin.getBoard(), possibleCase);

        HeuristicValue heuResult;
        Board copy;
        
        BOOST_FOREACH(Coord& pos, possibleCase) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(pos.x, pos.y, Referee::opponant(_player)) > -1) {
                heuResult = max_ab(depth + 1, refcopy, _heuristic(copy, _player, depth), alpha, beta);
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

    HeuristicValue max_ab(unsigned int depth, Referee& reforigin, HeuristicValue boardHeuristic, HeuristicValue alpha, HeuristicValue beta) {
        if (depth >= DEPTH || reforigin.checkWin() != 0) {
            unsigned int winner = reforigin.checkWin();
            if (winner == this->getPlayerNum())
                return _heuristic.victory(depth);
            else if (winner)
                return _heuristic.defeat(depth);
            return boardHeuristic;
        }

        CoordContainer possibleCase;

        possibleCase.reserve(_sizeCoord);
        _searchCase(reforigin.getBoard(), possibleCase);

        HeuristicValue heuResult;
        Board copy;

        BOOST_FOREACH(Coord& pos, possibleCase) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(pos.x, pos.y, _player) > -1) {
                heuResult = min_ab(depth + 1, refcopy, _heuristic(copy, _player, depth), alpha, beta);
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

    HeuristicValue min(unsigned int depth, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth >= DEPTH || reforigin.checkWin() != 0) {
            unsigned int winner = reforigin.checkWin();
            if (winner == _player)
                return _heuristic.victory(depth);
            else if (winner)
                return _heuristic.defeat(depth);
            return boardHeuristic;
        }

        CoordContainer possibleCase;

        possibleCase.reserve(_sizeCoord);
        _searchCase(reforigin.getBoard(), possibleCase);

        HeuristicValue heuResult;
        HeuristicValue result = _heuristic.victory(depth);
        Board copy;

        BOOST_FOREACH(Coord& pos, possibleCase) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(pos.x, pos.y, Referee::opponant(_player)) > -1) {
                heuResult = max(depth + 1, refcopy, _heuristic(copy, _player, depth));
                if (heuResult < result)
                    result = heuResult;
            }
        }

        return result;
    }

    HeuristicValue max(unsigned int depth, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth >= DEPTH || reforigin.checkWin() != 0) {
            unsigned int winner = reforigin.checkWin();
            if (winner == this->getPlayerNum())
                return _heuristic.victory(depth);
            else if (winner)
                return _heuristic.defeat(depth);
            return boardHeuristic;
        }

        CoordContainer possibleCase;

        possibleCase.reserve(_sizeCoord);
        _searchCase(reforigin.getBoard(), possibleCase);

        HeuristicValue heuResult;
        HeuristicValue result = _heuristic.defeat(depth);
        Board copy;

        BOOST_FOREACH(Coord& pos, possibleCase) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(pos.x, pos.y, _player) > -1) {
                heuResult = min(depth + 1, refcopy, _heuristic(copy, _player, depth));
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
