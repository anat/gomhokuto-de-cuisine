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


void HPlayer::doAction(Board& gameboard, Referee& referee)
{
    int x = 0, y = 0;
    int res = 0;
    do 
    {
        gameboard.DumpBoard();
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
        else
            addPawnTaken(res);
    }
    while (res == -1);
}

