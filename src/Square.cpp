
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
    std::cout << "Bit field dump" << std::endl;
    std::cout << "player : " << GET_PLAYER(_data) << std::endl;
    std::cout << "is takable : " << GET_TAKABLE(_data) << std::endl;
    std::cout << "diagl : " << GET_DIAGL(_data) << std::endl;
    std::cout << "diagr : " << GET_DIAGR(_data) << std::endl;
    std::cout << "horz : " << GET_HORZ(_data) << std::endl;
    std::cout << "vert : " << GET_VERT(_data) << std::endl;
    std::cout << "diagl_block : " << GET_DIAGL_BLOCK(_data) << std::endl;
    std::cout << "diagr_block : " << GET_DIAGR_BLOCK(_data) << std::endl;
    std::cout << "horz_block : " << GET_HORZ_BLOCK(_data) << std::endl;
    std::cout << "vert_block : " << GET_VERT_BLOCK(_data) << std::endl;
}


