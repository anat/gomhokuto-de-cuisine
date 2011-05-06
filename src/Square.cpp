
#include "Square.hpp"

Square::Square() : _player(NOPLAYER) {
    
}


Square::Player Square::getPalyer()
{
    return (_player);
}

bool Square::isEndLink()
{

}

void Square::setPlayer(Player player)
{
    _player = player;
}

void Square::setStatusLink(int type, char value)
{
    if (type & END)
        _status_link[_player + 2][type&~END] += value;
    else
        _status_link[_player][type] += value;
}

char * Square::getLinkType(int type)
{
    if (type & END)
        return (_status_link[_player + 2]);
    return (_status_link[_player]);
}