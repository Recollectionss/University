//
//  Employee.h
//  DataBase-lab1
//
//  Created by Илья Гончаренко on 22.02.2024.
//

#ifndef Employee_h
#define Employee_h

#include <chrono>
#include <iostream>

struct Employee {
    int id;
    char fullName[30];
    char position[20];
    //std::chrono::system_clock::time_point dateOfBirth;
    int departmentCode;
    
    bool toDelete;
    int nextEmployee =-1;
};

#endif /* Employee_h */
