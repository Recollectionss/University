//
//  ConcertHall.hpp
//  DataBase-lab1
//


#ifndef ConcertHall_hpp
#define ConcertHall_hpp

#include <stdio.h>
#include <iostream>
#include <chrono>


struct ConcertHall{
    int id;
    char fullName[30];
    char address[30];
    int floor=0;
    int numberOfStaff;
    int countOfSeets=0;
    bool toDelete;
};

#endif /* ConcertHall_hpp */
