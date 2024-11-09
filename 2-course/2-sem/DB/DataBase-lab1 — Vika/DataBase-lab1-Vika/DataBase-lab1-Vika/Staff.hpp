//
//  Staff.hpp
//  DataBase-lab1
//


#ifndef Staff_hpp
#define Staff_hpp

#include <stdio.h>

#include <chrono>
#include <iostream>

struct Staff {
    int id;
    char fullName[30];
    char position[20];
    //std::chrono::system_clock::time_point dateOfBirth;
    int age=0;
    bool sex;//true man \ false famale
    int ConcertHallCode=0;
    
    bool toDelete;
    int nextStaff =-1;
};

#endif /* Staff_hpp */
