/* 
 * File:   APlayer.cop
 * Author: cedric.creusot
 *
 * Created on May 8, 2011, 11:32 AM
 */

#include "APlayer.h"

APlayer::APlayer() : _nbPawnTaken(0)
{
    
}

APlayer::~APlayer()
{
    
}

int const APlayer::getNBPawnTaken() const
{
    return _nbPawnTaken;
}

void APlayer::incrementPawnTaken()
{
    _nbPawnTaken++;
}