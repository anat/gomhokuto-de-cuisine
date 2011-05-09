/* 
 * File:   APlayer.cop
 * Author: cedric.creusot
 *
 * Created on May 8, 2011, 11:32 AM
 */

#include "APlayer.h"

APlayer::APlayer(Square::Player player) : _nbPawnTaken(0), _player(player)
{
    
}

APlayer::~APlayer()
{
    
}

int const APlayer::getNBPawnTaken() const
{
    return (_nbPawnTaken);
}

void APlayer::incrementPawnTaken()
{
    _nbPawnTaken++;
}

Square::Player & APlayer::getPlayerNum()
{
    return (_player);
}