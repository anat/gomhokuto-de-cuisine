
#include "Square.hpp"

Square::Square() : _player(NOPLAYER), _value() {
    _value.resize(VEC_SIZE);
    for (int i = 0; i < VEC_SIZE; ++i)
        _value[i].resize(BYTE_SIZE);
}

Square::Player Square::getPlayer()
{
    return (_player);
}

void Square::setPlayer(Player player)
{
    _player = player;
}

void   Square::modifValue(Player player, int num_case, bool increment)
{
    if (increment)
        increment(player, num_case);
    else
        decrement(player, num_case);
}

void   Square::increment(Player player, int num_case)
{
    _value[(int) player][num_case]++;
}

void   Square::decrement(Player player, int num_case)
{
    _value[(int) player][num_case]--;    
}

char * Square::getValues(Player player) const
{
    return (_value[(int)player]);
}
