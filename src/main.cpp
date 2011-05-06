/* 
 * File:   main.cpp
 * Author: fancel
 *
 * Created on April 30, 2011, 6:27 AM
 */

#include <iostream>

#include "Board.hpp"

int main(void) {
    std::cout << "hello world" << std::endl;
    Board plateau;
    if (plateau(1, 2).getPlayer() == Square::NOPLAYER)
        std::cout << "caca" << std::endl;

    return 0;
}

