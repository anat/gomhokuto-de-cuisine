/* 
 * File:   APlayer.cop
 * Author: cedric.creusot
 *
 * Created on May 8, 2011, 11:32 AM
 */

#include "APlayer.hpp"

APlayer::APlayer(unsigned int player) : _player(player)
{
    
}

APlayer::~APlayer()
{
    
}

unsigned int APlayer::getPlayerNum()
{
    return (_player);
}