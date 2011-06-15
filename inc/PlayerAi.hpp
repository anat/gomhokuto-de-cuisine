#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include <vector>
#include <set>

#include "Board.hpp"
#include "APlayer.hpp"

template < typename IHeuristic >
class PlayerAi : public APlayer
{
public:
    PlayerAi(unsigned int id) : APlayer(id), _heuristic()
    {}

    PlayerAi(const PlayerAi& orig)
    {
        this->operator =(orig);
    }

    ~PlayerAi()
    {}

    PlayerAi& operator=(const PlayerAi& orig)
    {
        if (this != &orig)
        {
            _heuristic = orig._heuristic;
        }
        return *this;
    }

    bool doAction(Board& gameboard, Referee& ref, int x, int y)
    {
        doMagic(gameboard, ref);
        return true;
    }

    IHeuristic::HeuristicValue doMagic(Board& origin, Referee& ref)
    {
        typename IHeuristic::HeuristicValue originValue = heuristic.getHeuristic(origin);
        std::set< Coord > possibleCase;

        searchCase(origin, possibleCase);
        std::set< Coord >::iterator it = possibleCase.begin();
        std::set< Coord >::iterator ite = possibleCase.end();

        while (it != ite)
        {
            if (ref.testPosition((*it).x, (*it).y, this->getPlayerNum()))
            {
                Board copy = origin;
                Referee copyRef(copy);
                int result = copyRef.tryPlaceRock((*it).x, (*it).y, this->getPlayerNum());
                if (result >= 0)
                {

                }
            }
            ++it;
        }


        return true;
    }
private:
    IHeuristic _heuristic;

    void searchCase(Board& game, std::set< Coord >& possibleCase)
    {
        unsigned int size = game.getSize();
        for (unsigned int x = 0; x < size; ++x)
        {
            for (unsigned int y = 0; y < size; ++y)
            {
                if (game(x, y).getData().player != 0)
                {
                    std::cout << "x " << x << " y " << y << std::endl;
                }
            }
        }
    }
};

#endif // PLAYERAI_HPP
