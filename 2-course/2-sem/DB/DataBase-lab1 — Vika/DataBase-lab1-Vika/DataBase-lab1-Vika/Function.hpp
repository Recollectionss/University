//
//  Function.hpp
//  DataBase-lab1
//


#ifndef Function_hpp
#define Function_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <limits>

#include <map>

#include "Staff.hpp"
#include "ConcertHall.hpp"


ConcertHall create_ConcertHall(std::map<int,int> &ConcertHall_id_and_numberRecord,std::map<int,int> &ConcertHallId_and_StaffIdp,ConcertHall d = { });
Staff create_Staff(std::map<int,int> &Staff_id_and_numberRecord,std::map<int,int> &ConcertHall_id_and_numberRecord,Staff e = { });

ConcertHall get_m(int id,std::map<int,int> &ConcertHall_id_and_numberRecord);
Staff get_s(int id,std::map<int,int> &Staff_id_and_numberRecord);

bool insert_m(ConcertHall& ConcertHall,std::map<int,int>& ConcertHall_id_and_numberRecord,std::map<int,int> & deletedConcertHall);
bool insert_s(Staff& Staff,std::map<int,int> &Staff_id_and_numberRecord,std::map<int,int> &ConcertHallId_and_StaffIdp,std::map<int,int>& deletedStaff,std::map<int,int> &ConcertHall_id_and_numberRecord);

bool delete_m(int id,std::map<int,int> &ConcertHall_id_and_numberRecord,std::map<int,int> &deletedConcertHall,std::map<int,int> &ConcertHallId_and_StaffIdp,std::map<int,int> &Staff_id_and_numberRecord,std::map<int,int>& deletedStaff);
bool delete_s(int id,std::map<int,int>& Staff_id_and_numberRecord,std::map<int,int>& ConcertHallId_and_StaffIdp,std::map<int, int>& deletedStaff,std::map<int,int> &ConcertHall_id_and_numberRecord);

bool update_m(ConcertHall& ConcertHall,std::map<int,int> &ConcertHall_id_and_numberRecord);
bool update_s(Staff& Staff,int prevConcertHallCode,std::map<int,int> &Staff_id_and_numberRecord,std::map<int,int> &ConcertHallId_and_StaffIdp,std::map<int,int> &ConcertHall_id_and_numberRecord,std::map<int, int>& deletedStaff);

int calc_m(std::map<int,int> &ConcertHall_id_and_numberRecord);
int calc_s();

std::vector<ConcertHall> ut_m();
std::vector<Staff> ut_s();

void print_ConcertHalls(std::vector<ConcertHall>& ConcertHalls);
void print_Staffs(std::vector<Staff>& Staffs);

void print_ConcertHall(ConcertHall& ConcertHall);
void print_Staff(Staff& Staff);

void deleteALL_Data();

//template<typename KeyType, typename ValueType>
std::map<int, int> readMapFromFile(const std::string& filename);


void writeMapToFile(const std::map<int, int>& input_map, const std::string& filename);

bool isInteger(const std::string& s);
template<size_t N>
void readConsoleInput(char (&input)[N]);

void findDeletedRecords(std::map<int,int>& deletedStaff,std::map<int,int>& deletedDerpartment);

//std::map<int,int> readDeletingConcertHall();
//std::map<int,int> readDeletingStaff();
#endif /* Function_hpp */
