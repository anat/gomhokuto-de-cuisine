/* 
 * File:   Square.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 12:19 PM
 */

#ifndef SQUARE_HPP
#define	SQUARE_HPP

#define VEC_SIZE 3
#define BYTE_SIZE 9

#include <vector>

class Square {
public:

    enum Player {
        NOPLAYER,
        PLAYER1,
        PLAYER2
    };

    enum Value {
        LINK1,
        LINK2,
        LINK3,
        LINK4,
        LINK5,
        END_LINK2,
        END_LINK3,
        END_LINK4,
        END_LINK5
    };

private:
    std::vector< std::vector<char> > _value;
    Player _player;

public: //la flemme de faire des get/setter
    int _horz, _vert, _diagl, _diagr; // pas opti pour l'instant

public:
    Square();
    Player getPlayer();
    void setPlayer(Player player);
    std::vector<char> const & getValues(Player player) const;
    void modifValue(Player player, int num_case, bool increment);
private:
    void increment(Player player, int num_case);
    void decrement(Player player, int num_case);
};

#endif	/* SQUARE_HPP */

