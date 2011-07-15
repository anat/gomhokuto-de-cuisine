/* 
 * File:   HPlayer.cpp
 * Author: cedric.creusot
 * 
 * Created on May 8, 2011, 2:13 PM
 */

#include <iostream>
#include "HPlayer.hpp"

HPlayer::HPlayer(unsigned int player) : APlayer(player) {
}

HPlayer::~HPlayer() {
}


bool HPlayer::doAction(Board&, Referee& referee, int x, int y)
{
    int res = 0;
    if (x < 0 && y < 0)
    {
        do 
        {
            //gameboard.DumpBoard();
            std::cout << "Player " << this->getPlayerNum();
            std::cout << " you want play on x :";
            std::cin >> x;
            std::cout << " y : ";
            std::cin >> y;
            res = referee.tryPlaceRock(x,y, this->getPlayerNum());
            if (res == -1) {
                std::cout << "you can't play here x : " << x;
                std::cout << " y : " << y << std::endl;
            }
            std::cout << "RES : " << res << std::endl;
            std::cout << referee.getScore(getPlayerNum()) << std::endl;
        }
        while (res == -1);
    }
    else
    {
        res = referee.tryPlaceRock(x, y, this->getPlayerNum());
        if (res == -1)
            return false;
    }
    return true;
}
