
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
    std::cout << "Bit field dump" << std::endl;
    std::cout << "player : " << data.player << std::endl;
    std::cout << "is takable : " << data.is_takable << std::endl;
    std::cout << "diagl : " << data.diagl << std::endl;
    std::cout << "diagr : " << data.diagr << std::endl;
    std::cout << "horz : " << data.horz << std::endl;
    std::cout << "vert : " << data.vert << std::endl;
    std::cout << "value : " << this->getRawData()<< std::endl;
    std::cout << "value hex : 0x" << std::hex;
    std::cout << this->getRawData() << std::endl;
    std::cout << "[.....]" << std::endl;
    std::cout << "Raw Data Bit Mask dump" << std::endl;
    std::cout << "player : " << GET_PLAYER(_data) << std::endl;
    std::cout << "is takable : " <<  GET_TAKABLE(_data) << std::endl;
    std::cout << "diagl : " << GET_DIAGL(_data) << std::endl;
    std::cout << "diagr : " << GET_DIAGR(_data) << std::endl;
    std::cout << "horz : " << GET_HORZ(_data) << std::endl;
    std::cout << "vert : " << GET_VERT(_data) << std::endl;
    std::cout << "value : " << std::dec << this->getRawData()<< std::endl;
    std::cout << "value hex : 0x" << std::hex;
    std::cout << this->getRawData() << std::endl;
}

unsigned int Square::getHorz() const
{
    return GET_HORZ(_data);
}

unsigned int Square::getVert() const
{
    return GET_VERT(_data);
}

unsigned int Square::getDiagl() const
{
    return GET_DIAGL(_data);
}

unsigned int Square::getDiagr() const
{
    return GET_DIAGR(_data);
}

void Square::setVert(unsigned int lineSize)
{
    getData().vert = lineSize;
}

void Square::setHorz(unsigned int lineSize)
{
    getData().horz = lineSize;
}

void Square::setDiagl(unsigned int lineSize)
{
    getData().diagl = lineSize;
}

void Square::setDiagr(unsigned int lineSize)
{
    getData().diagr = lineSize;
}
