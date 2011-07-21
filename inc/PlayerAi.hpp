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

    enum {
        DEPTH = 2
    };

    PlayerAi(unsigned int id) : APlayer(id), _heuristic(), _searchCase(), _maxDepth(2), _sizeCoord(8), _alpha(), _beta() {
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

        possibleCase.reserve(_sizeCoord);

        _searchCase(gameboard, possibleCase);

        if (_sizeCoord < possibleCase.size())
            _sizeCoord = possibleCase.size();

        typename CoordContainer::iterator it = possibleCase.begin();
        typename CoordContainer::iterator ite = possibleCase.end();

        heuResult.resize(possibleCase.size());

        HeuristicValue BestHeu = _heuristic.defeat(0);
        Coord bestMove;

        _alpha = _heuristic.defeat(0);
        _beta = _heuristic.victory(0);
        unsigned int i = 0;
        std::cout << "depth max " << _maxDepth << std::endl;
        std::cout << "base coord " << heuResult.size() << std::endl;
        boost::thread_group threadGroup;

        while (it != ite) {
            heuResult[i].second = *it;

            boost::function< void() > func = boost::bind(
                    &PlayerAi::explore, this,
                    gameboard,
                    ref,
                    heuResult[i].second,
                    &heuResult[i].first
                    );

            func();

            ++i;
            ++it;
        }

        threadGroup.join_all();

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
            *result = min_ab(1, refcopy, _heuristic(gameBoard, _player, 1));
        } else {
            *result = _heuristic.defeat(0);
        }
    }

    HeuristicValue min_ab(unsigned int depth, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth >= _maxDepth || reforigin.checkWin() != 0) {
            unsigned int winner = reforigin.checkWin();
            //if (winner)
            //reforigin.getBoard().DumpBoard();
            if (winner == _player)
                return _heuristic.victory(depth);
            else if (winner)
                return _heuristic.defeat(depth);
            return boardHeuristic;
        }

        CoordContainer possibleCase;

        possibleCase.reserve(_sizeCoord);
        _searchCase(reforigin.getBoard(), possibleCase);

        typename CoordContainer::const_iterator it = possibleCase.begin();
        typename CoordContainer::const_iterator ite = possibleCase.end();

        HeuristicValue heuResult;
        HeuristicValue result = _heuristic.victory(depth);
        Board copy;

        unsigned int good = 5;
        while (it != ite && good) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(it->x, it->y, Referee::opponant(_player)) > -1) {
                heuResult = max_ab(depth + 1, refcopy, _heuristic(copy, _player, depth));
                _betaMut.lock();
                if (heuResult < _beta)
                    _beta = heuResult;
                _betaMut.unlock();
                if (heuResult < result)
                    result = heuResult;
                _alphaMut.lock();
                _betaMut.lock();
                if (_beta <= _alpha) {
                    std::cout << "blocked" << std::endl;
                    good = 0;
                }
                _alphaMut.unlock();
                _betaMut.unlock();
            }
            ++it;
        }

        return result;
    }

    HeuristicValue max_ab(unsigned int depth, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth >= _maxDepth || reforigin.checkWin() != 0) {
            unsigned int winner = reforigin.checkWin();
            //if (winner)
            //reforigin.getBoard().DumpBoard();
            if (winner == this->getPlayerNum())
                return _heuristic.victory(depth);
            else if (winner)
                return _heuristic.defeat(depth);
            return boardHeuristic;
        }

        CoordContainer possibleCase;

        possibleCase.reserve(_sizeCoord);
        _searchCase(reforigin.getBoard(), possibleCase);

        typename CoordContainer::const_iterator it = possibleCase.begin();
        typename CoordContainer::const_iterator ite = possibleCase.end();

        HeuristicValue heuResult;
        HeuristicValue result = _heuristic.defeat(depth);
        Board copy;

        unsigned int good = 5;

        while (it != ite && good) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(it->x, it->y, _player) > -1) {
                heuResult = min_ab(depth + 1, refcopy, _heuristic(copy, _player, depth));
                _alphaMut.lock();
                if (heuResult > _alpha)
                    _alpha = heuResult;
                _alphaMut.unlock();
                if (heuResult > result)
                    result = heuResult;
                _alphaMut.lock();
                _betaMut.lock();
                if (_beta <= _alpha) {
                    std::cout << "blocked" << std::endl;
                    good = 0;
                }
                _alphaMut.unlock();
                _betaMut.unlock();
            }
            ++it;
        }

        return result;
    }

    HeuristicValue min(unsigned int depth, Referee& reforigin, HeuristicValue boardHeuristic) {
        //std::cout << "min" << std::endl;
        if (depth >= _maxDepth || reforigin.checkWin() != 0) {
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

        typename CoordContainer::const_iterator it = possibleCase.begin();
        typename CoordContainer::const_iterator ite = possibleCase.end();

        HeuristicValue heuResult;
        HeuristicValue result = _heuristic.victory(depth);
        Board copy;

        while (it != ite) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(it->x, it->y, Referee::opponant(_player)) > -1) {
                heuResult = max(depth + 1, refcopy, _heuristic(copy, _player, depth));
                if (heuResult < result)
                    result = heuResult;
            }
            ++it;
        }

        return result;
    }

    HeuristicValue max(unsigned int depth, Referee& reforigin, HeuristicValue boardHeuristic) {
        if (depth >= _maxDepth || reforigin.checkWin() != 0) {
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

        typename CoordContainer::const_iterator it = possibleCase.begin();
        typename CoordContainer::const_iterator ite = possibleCase.end();

        HeuristicValue heuResult;
        HeuristicValue result = _heuristic.defeat(depth);
        Board copy;

        while (it != ite) {
            copy = reforigin.getBoard();
            Referee refcopy(reforigin, copy);

            if (refcopy.tryPlaceRock(it->x, it->y, _player) > -1) {
                heuResult = min(depth + 1, refcopy, _heuristic(copy, _player, depth));
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
    unsigned int _sizeCoord;
    HeuristicValue _alpha;
    HeuristicValue _beta;
    boost::mutex _alphaMut;
    boost::mutex _betaMut;
};

#endif // PLAYERAI_HPP
