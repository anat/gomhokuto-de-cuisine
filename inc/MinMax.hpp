/* 
 * File:   MinMax.hpp
 * Author: fancel
 *
 * Created on 27 July 2011, 15:23
 */

#ifndef MINMAX_HPP
#define	MINMAX_HPP

#include <boost/foreach.hpp>
#include <boost/thread.hpp>

#include "Coord.hpp"
#include "Referee.hpp"

template < typename IHeuristic, typename ISearchCase, unsigned int DEPTH >
struct MinMax {
    typedef typename IHeuristic::HeuristicValue HeuristicValue;
    typedef typename ISearchCase::CoordContainer CoordContainer;

    IHeuristic _heuristic;
    ISearchCase _searchCase;
    unsigned int _player;
    Board _gameBoard;
    Referee refcopy;
    Coord& _pos;
    HeuristicValue* _result;

    MinMax(unsigned int player, Board& gameBoard, Referee& ref, Coord& pos, HeuristicValue * result)
    : _heuristic(), _searchCase(), _player(player), _gameBoard(gameBoard), refcopy(ref, _gameBoard), _pos(pos), _result(result) {
    }

    void operator()() {
        run();
    }

    void run() {
        if (refcopy.tryPlaceRock(_pos.x, _pos.y, _player) > -1) {
            *_result = min_ab(DEPTH, _heuristic.defeat(0), _heuristic.victory(0));
        } else {
            *_result = _heuristic.defeat(0);
        }
    }

    HeuristicValue min_ab(unsigned int depth, HeuristicValue alpha, HeuristicValue beta) {
        if (!depth || refcopy.checkWin()) {
            unsigned int winner = refcopy.checkWin();
            if (winner == _player) {
                return _heuristic.victory(depth);
            } else if (winner) {
                return _heuristic.defeat(depth);
            }
            return _heuristic(refcopy.getBoard(), _player, depth);
        }

        CoordContainer possibleCase;

        _searchCase(refcopy.getBoard(), possibleCase);

        HeuristicValue heuResult;

        BOOST_FOREACH(Coord& pos, possibleCase) {
            if (refcopy.tryPlaceRock(pos.x, pos.y, Referee::opponant(_player)) > -1) {
                heuResult = max_ab(depth - 1, alpha, beta);
                if (heuResult <= alpha) {
                    refcopy.UndoLastAction();
                    return alpha;
                }
                if (heuResult < beta) {
                    beta = heuResult;
                }
                refcopy.UndoLastAction();
            }
        }

        return beta;
    }

    HeuristicValue max_ab(unsigned int depth, HeuristicValue alpha, HeuristicValue beta) {
        if (!depth || refcopy.checkWin()) {
            unsigned int winner = refcopy.checkWin();
            if (winner == _player) {
                return _heuristic.victory(depth);
            } else if (winner) {
                return _heuristic.defeat(depth);
            }
            return _heuristic(refcopy.getBoard(), _player, depth);
        }

        CoordContainer possibleCase;

        _searchCase(refcopy.getBoard(), possibleCase);

        HeuristicValue heuResult;

        BOOST_FOREACH(Coord& pos, possibleCase) {
            if (refcopy.tryPlaceRock(pos.x, pos.y, _player) > -1) {
                heuResult = min_ab(depth - 1, alpha, beta);
                if (heuResult >= beta) {
                    refcopy.UndoLastAction();
                    return beta;
                }
                if (heuResult > alpha) {
                    alpha = heuResult;
                }
                refcopy.UndoLastAction();
            }
        }

        return alpha;
    }
};

#endif	/* MINMAX_HPP */

