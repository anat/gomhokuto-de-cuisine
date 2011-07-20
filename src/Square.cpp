
#include <iostream>
#include "Square.hpp"

Square::Square() : _mut(), _data(0) {
    
}

Square::~Square()
{
    
}

int32_t Square::getRawData() const
{
    boost::lock_guard<boost::mutex> lock(_mut);
    return (_data);
}

void Square::setRawData(int32_t mask)
{
    _mut.lock();
    _data = mask;
    _mut.unlock();
}

void Square::dumpData() const
{
    boost::lock_guard<boost::mutex> lock(_mut);
    const Square::Data & data = this->getData();
    std::cout << "Bit field dump" << std::endl;
    std::cout << "player : " << data.player << std::endl;
    std::cout << "is takable : " << data.is_takable << std::endl;
    std::cout << "diagl : " << data.diagl << std::endl;
    std::cout << "diagr : " << data.diagr << std::endl;
    std::cout << "horz : " << data.horz << std::endl;
    std::cout << "vert : " << data.vert << std::endl;
    std::cout << "diagl_block : " << data.diagl_block << std::endl;
    std::cout << "diagr_block : " << data.diagr_block << std::endl;
    std::cout << "horz_block : " << data.horz_block << std::endl;
    std::cout << "vert_block : " << data.vert_block << std::endl;
}


