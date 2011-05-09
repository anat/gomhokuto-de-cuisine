/* 
 * File:   HPlayer.cpp
 * Author: cedric.creusot
 * 
 * Created on May 8, 2011, 2:13 PM
 */

#include "HPlayer.h"

HPlayer::HPlayer(Square::Player player) : APlayer(player) {
}

HPlayer::~HPlayer() {
}


void HPlayer::doAction(Board& gameboard, Referee& referee)
{
    referee.tryPlaceRock(0,0, this->getPlayerNum());
}

