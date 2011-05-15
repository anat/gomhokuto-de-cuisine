/* 
 * File:   APlayer.cop
 * Author: cedric.creusot
 *
 * Created on May 8, 2011, 11:32 AM
 */

#include "APlayer.hpp"

APlayer::APlayer(unsigned int player) : _nbPawnTaken(0), _player(player)
{
    
}

APlayer::~APlayer()
{
    
}

int APlayer::getNBPawnTaken() const
{
    return (_nbPawnTaken);
}

void APlayer::addPawnTaken(int nb)
{
    _nbPawnTaken += nb;
}

unsigned int APlayer::getPlayerNum()
{
    return (_player);
}