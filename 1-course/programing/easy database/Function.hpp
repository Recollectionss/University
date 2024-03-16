//
//  Function.hpp
//  Лаба 1 версия 3.0(тест на исправление)
//
//  Created by Илья Гончаренко on 13.02.2023.
//

#ifndef Function_hpp
#define Function_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct student{
    string surname,
            name,
            patronymic;
    string group;

};

struct teachers{
    string surname,
            name,
            patronymic;
    int cabinet;
};



//function prototypes

void SaveDataStudent(student* &s ,int &n);
void SaveDataTeachers(teachers* &t, int &n);

void ReadDataStudent(student* &s,int &n);
void ReadDataTeachers(teachers* &t,int &n);


void AddDateStudent (student* (&s), int &n);
void AddDateTeachers (teachers* (&t), int &n);

void PrintStudent(student* (&s), int &n);
void PrintTeachers(teachers* (&t), int &n);


void DataChangeStudent(student* (&s), int &n);
void DataChangeTeachers(teachers* (&t), int &n);


void DeleteDataStudent(student* (&s), int &n);
void DeleteDataTeahers(teachers* (&t), int &n);


void CopyStudent(student* (&s_n), student* (&s_o), int n);
void CopyTeachers(teachers* (&t_n), teachers* (&t_o), int n);







#endif /* Function_hpp */
