//
//  Function.hpp
//  DataBase-lab1
//
//  Created by Илья Гончаренко on 22.02.2024.
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

#include "Employee.h"
#include "Department.h"


Department create_Department(std::map<int,int> &department_id_and_numberRecord,std::map<int,int> &departmentId_and_EmployeeIdp,Department d = { });
Employee create_Employee(std::map<int,int> &employee_id_and_numberRecord,std::map<int,int> &department_id_and_numberRecord,Employee e = { });

Department get_m(int id,std::map<int,int> &department_id_and_numberRecord);
Employee get_s(int id,std::map<int,int> &employee_id_and_numberRecord);

bool insert_m(Department& department,std::map<int,int>& department_id_and_numberRecord,std::map<int,int> & deletedDepartment);
bool insert_s(Employee& employee,std::map<int,int> &employee_id_and_numberRecord,std::map<int,int> &departmentId_and_EmployeeIdp,std::map<int,int>& deletedEmployee,std::map<int,int> &department_id_and_numberRecord);

bool delete_m(int id,std::map<int,int> &department_id_and_numberRecord,std::map<int,int> &deletedDepartment,std::map<int,int> &departmentId_and_EmployeeIdp,std::map<int,int> &employee_id_and_numberRecord,std::map<int,int>& deletedEmployee);
bool delete_s(int id,std::map<int,int>& employee_id_and_numberRecord,std::map<int,int>& departmentId_and_EmployeeIdp,std::map<int, int>& deletedEmployee,std::map<int,int> &department_id_and_numberRecord);

bool update_m(Department& department,std::map<int,int> &department_id_and_numberRecord);
bool update_s(Employee& employee,int prevDepartmentCode,std::map<int,int> &employee_id_and_numberRecord,std::map<int,int> &departmentId_and_EmployeeIdp,std::map<int,int> &department_id_and_numberRecord,std::map<int, int>& deletedEmployee);

int calc_m(std::map<int,int> &department_id_and_numberRecord);
int calc_s();

std::vector<Department> ut_m();
std::vector<Employee> ut_s();

void print_Departments(std::vector<Department>& departments);
void print_Employees(std::vector<Employee>& employees);

void print_Department(Department& department);
void print_Employee(Employee& employee);

void deleteALL_Data();

//template<typename KeyType, typename ValueType>
std::map<int, int> readMapFromFile(const std::string& filename);


void writeMapToFile(const std::map<int, int>& input_map, const std::string& filename);

bool isInteger(const std::string& s);
template<size_t N>
void readConsoleInput(char (&input)[N]);

void findDeletedRecords(std::map<int,int>& deletedEmployee,std::map<int,int>& deletedDerpartment);

std::vector<Employee> printAllEmployeeInThisDepartment(Department department,std::map<int, int>& departmentId_and_EmployeeId,std::map<int,int>& employee_id_and_numberRecord);
#endif /* Function_hpp */
