//
//  Department.h
//  DataBase-lab1
//
//  Created by Илья Гончаренко on 22.02.2024.
//

#ifndef Department_h
#define Department_h

#include <iostream>
#include <chrono>


struct Department{
    int id;
    char fullName[30];
//    std::chrono::system_clock::time_point dateOfCreation;
    int numberOfEmployee;
    bool toDelete;
};

#endif /* Department_h */
