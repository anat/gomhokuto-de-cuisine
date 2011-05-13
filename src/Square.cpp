
#include <iostream>
#include "Square.hpp"

Square::Square() : _data(0) {
    
}

Square::~Square()
{
    
}

int32_t Square::getRawData() const
{
    
    return (_data);
}

void Square::setRawData(int32_t mask)
{
    _data = mask;
}

Square::Data & Square::getData()
{
  return (*reinterpret_cast<Square::Data*>(&_data));  
}

void Square::setData(Square::Data & data)
{
    _data = (int32_t)(*reinterpret_cast<int32_t*>(&data));
}

void Square::dumpData()
{
    Square::Data & data = this->getData();
    std::cout << "player : " << data.player << std::endl;
    std::cout << "is takable : " << data.is_takable << std::endl;
    std::cout << "diagl : " << data.diagl << std::endl;
    std::cout << "diagr : " << data.diagr << std::endl;
    std::cout << "horz : " << data.horz << std::endl;
    std::cout << "vert : " << data.vert << std::endl;
    std::cout << "value : " << this->getRawData()<< std::endl;
    std::cout << "value hex : " << std::hex << std::showbase;
    std::cout << this->getRawData() << std::endl;
}