//
//  Function.cpp
//  DataBase-lab1
//
//  Created by Илья Гончаренко on 22.02.2024.
//

#include "Function.hpp"
#include <ctime>

Department create_Department(std::map<int,int>& department_id_and_numberRecord, std::map<int,int>& departmentId_and_EmployeeIdp,Department d) {
    Department department;


    std::cout << "Enter department full name: ";
    readConsoleInput(department.fullName);

    std::cout << "Enter number of employees (>1): ";
    std::cin >> department.numberOfEmployee;


    while (department.numberOfEmployee < 1) {
        std::cout << "Invalid number of employees. Please enter a number greater than 1." << std::endl;
        std::cin.clear(); // Очистить флаги ошибок ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter number of employees (>1): ";
        std::cin >> department.numberOfEmployee;

        // Пропустить оставшийся символ новой строки во входном буфере
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    //std::cout<<"LLLLLL"<<d.id<<'\n';
    if (d.id==0) {
        department.id = department_id_and_numberRecord.size() + 1;
    }else{
        department.id=d.id;
    }
    //department.id = department_id_and_numberRecord.size() + 1;
    departmentId_and_EmployeeIdp[department.id] = -1;
    department.toDelete = false;

    return department;
}


Employee create_Employee(std::map<int,int>& employee_id_and_numberRecord, std::map<int,int>& department_id_and_numberRecord,Employee e) {
    Employee employee;
    std::string input;
    
    std::cout << "Enter employee full name: ";
    readConsoleInput(employee.fullName);
    
    std::cout << "Enter position: ";
    readConsoleInput(employee.position);
    
    
    do {
        std::cout << "Enter the department Code: ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!isInteger(input) || std::stoi(input) <= 0 || get_m(std::stoi(input), department_id_and_numberRecord).id == 0);
    
    employee.departmentCode = std::stoi(input);
    if (e.id==0) {
        employee.id = employee_id_and_numberRecord.size() + 1;
    }else{
        employee.id = e.id;
    }
    employee_id_and_numberRecord[employee.id]=-1;
    employee.toDelete = false;
    
    return employee;
}

Department get_m(int id,std::map<int,int> &department_id_and_numberRecord){
    try {
        std::ifstream department_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Department.dat", std::ios::binary);
        if (!department_file.is_open()) {
            throw std::runtime_error("Faild open department_file /get_m");
        }
        
        
        
        std::streamoff offset = (static_cast<std::streamoff>(department_id_and_numberRecord[id]-1 ) * sizeof(Department))/*-sizeof(Department)*/;
        department_file.seekg(offset);
        
        
        Department department;
        if (!department_file.read(reinterpret_cast<char*>(&department), sizeof(Department))) {
                    throw std::runtime_error("Failed to read from department_file /get_m");
                }
        
        if (department.id!=id) {
            std::cout<<department.id<<'\n'<<'\n';
            throw std::runtime_error("Something wrong with read /get_m");
        }
        
        
        return department;
        
    }catch(std::runtime_error& e){
        std::cerr<<"An exception occurred: "<<e.what()<<'\n';
    }
    return {0};
}
Employee get_s(int id,std::map<int,int> &employee_id_and_numberRecord){
    try {
        auto it = employee_id_and_numberRecord.rbegin();
        std::cout<<"RBEGIN: "<<it->first<<'\n';
//        if (id > it->first) {
//            return {-1};
//        }
        
        std::ifstream employee_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Employee.dat",std::ios::binary);
        if(!employee_file.is_open()){
            employee_file.close();
            throw std::runtime_error("Failde open employee.dat /get_s");
        }
        //if (id!=1) {
            std::streamoff offset = static_cast<std::streamoff>(employee_id_and_numberRecord[id]) * sizeof(Employee);
            employee_file.seekg(offset);
       // }
        
        Employee employee;
        if (!employee_file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
            employee_file.close();
            throw std::runtime_error("Faild read from employee_file /get_s");
        }
       
        employee_file.close();
        return employee;
    } catch (std::runtime_error& e) {
        std::cerr<<"An exception occurred: "<<e.what();
        
    }
    return {-2};
}

bool insert_m(Department& department,std::map<int,int>& department_id_and_numberRecord,std::map<int,int> & deletedDepartment){
    try{
        std::fstream department_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Department.dat",std::ios::binary | std::ios::in |std::ios::out);
        if (!department_file.is_open()) {
            department_file.close();
            throw std::runtime_error("Failed open department_file /insert_m");
        }
        
        if (!deletedDepartment.empty()) {
            auto it = deletedDepartment.begin();
            std::streamoff offset = static_cast<std::streamoff>(it->second)* sizeof(Department);
            department_file.seekg(offset);
            deletedDepartment.erase(it);
        }else   {
            department_file.close();
            std::ofstream department_file_f("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Department.dat",std::ios::binary | std::ios::app);
            department_file_f.write(reinterpret_cast<char*>(&department), sizeof(Department));
            department_id_and_numberRecord[department.id] = department_file_f.tellp()/sizeof(Department);
        }
        department_file.close();
        return true;
        
    }catch(std::runtime_error& e){
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return false;
}
bool insert_s(Employee& employee,std::map<int,int> &employee_id_and_numberRecord,std::map<int,int> &departmentId_and_EmployeeIdp,std::map<int,int>& deletedEmployee,std::map<int,int> &department_id_and_numberRecord){

    try {
            std::fstream employee_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Employee.dat",std::ios::binary | std::ios::in |std::ios::out);
            if (!employee_file.is_open()) {
                employee_file.close();
                throw std::runtime_error("Failed open employee_file /insert_s");
            }
        
            if (!deletedEmployee.empty()) {
                auto it = deletedEmployee.begin();
                std::streamoff offset = static_cast<std::streamoff>(it->second) * sizeof(Department);
                employee_file.seekg(offset);
                deletedEmployee.erase(it);
            }
                
                employee_file.close();
                std::ofstream employee_file_write("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Employee.dat",std::ios::binary | std::ios::app );
                
                //        employee_file_write.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
                
                
                if (departmentId_and_EmployeeIdp[employee.departmentCode]== -1) {
                    departmentId_and_EmployeeIdp[employee.departmentCode]=employee.id;
                }else{
                    std::cout<<"LOX\n";
                    Employee last_employee = get_s(departmentId_and_EmployeeIdp[employee.departmentCode], employee_id_and_numberRecord);
                    while (last_employee.nextEmployee!= -1) {
                        last_employee = get_s(last_employee.nextEmployee, employee_id_and_numberRecord);
                    }
                    last_employee.nextEmployee=employee.id;
                    update_s(last_employee, last_employee.departmentCode, employee_id_and_numberRecord, departmentId_and_EmployeeIdp, department_id_and_numberRecord, deletedEmployee);
                    std::cout<<last_employee.id<<":ID LAST\n";
                    std::cout<<employee.id<<":ID NEXT\n";
                    
                    int numberRecord = employee_file_write.tellp()/sizeof(Employee);
                    employee_id_and_numberRecord[employee.id] = numberRecord;
                    employee_file_write.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
                    employee_file.close();
                    return true;
                }
        int numberRecord = employee_file_write.tellp()/sizeof(Employee)/*-sizeof(Employee)*/;
        employee_id_and_numberRecord[employee.id] = numberRecord;
        employee_file_write.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
        employee_file.close();
                return true;
            
            
    } catch (std::runtime_error& e) {
           std::cerr<<"An exeption occured: "<<e.what()<<'\n';
       }
       return false;
}
//
bool delete_m(int id,std::map<int,int> &department_id_and_numberRecord,std::map<int,int> &deletedDepartment,std::map<int,int> &departmentId_and_EmployeeIdp,std::map<int,int> &employee_id_and_numberRecord,std::map<int,int>& deletedEmployee){
    try {
        std::fstream department_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Department.dat", std::ios::binary | std::ios::in |std::ios::out);
        if (!department_file.is_open()) {
            throw std::runtime_error("Failed open department_file /delete_m ");
        }
        
        
        Department department;
        department = get_m(id,department_id_and_numberRecord);
        department.toDelete=true;
        

        std::streamoff offset = static_cast<std::streamoff>(department_id_and_numberRecord[id] - 1) * sizeof(Department);
        department_file.seekg(offset);
        
        department_file.write(reinterpret_cast<char*>(&department), sizeof(Department));
        if (department_file.fail()) {
            throw std::runtime_error("Faild write department_file /delete_m ");
        }
        
        //std::cout<<"Employee ID VALUE: "<<departmentId_and_EmployeeIdp[department.id]<<'\n';
        
        if (departmentId_and_EmployeeIdp[department.id]!= -1) {
            Employee last_employee = get_s(departmentId_and_EmployeeIdp[department.id], employee_id_and_numberRecord);
            if (last_employee.nextEmployee != -1) {
                while (last_employee.nextEmployee != -1) {
                    delete_s(last_employee.id, employee_id_and_numberRecord, departmentId_and_EmployeeIdp, deletedEmployee,department_id_and_numberRecord);
                    last_employee = get_s(last_employee.nextEmployee, employee_id_and_numberRecord);
                }
            }
            delete_s(last_employee.id, employee_id_and_numberRecord, departmentId_and_EmployeeIdp, deletedEmployee,department_id_and_numberRecord);
        }
        
        departmentId_and_EmployeeIdp.erase(department.id);
        
        auto it = department_id_and_numberRecord.find(department.id);
        deletedDepartment[it->first]=it->second;
        department_id_and_numberRecord.erase(it);
        
        
        
        return true;
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return false;
}
bool delete_s(int id,std::map<int,int>& employee_id_and_numberRecord,std::map<int,int>& departmentId_and_EmployeeIdp,std::map<int, int>& deletedEmployee,std::map<int,int> &department_id_and_numberRecord){
    try {
        std::fstream employee_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Employee.dat", std::ios::binary | std::ios::in |std::ios::out );
        if (!employee_file.is_open()) {
            employee_file.close();
            throw std::runtime_error("Failed open employee_file /delete_s ");
        }
        
        
        Employee employee = get_s(id,employee_id_and_numberRecord);
        employee.toDelete = true;
        
        if (departmentId_and_EmployeeIdp[employee.departmentCode]==employee.id) {
            departmentId_and_EmployeeIdp[employee.departmentCode] = employee.nextEmployee;
            
            employee.toDelete=true;
            std::streamoff offset = static_cast<std::streamoff>(employee_id_and_numberRecord[employee.id]) * sizeof(Employee);
            employee_file.seekg(offset);
            
            employee_file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
            employee_file.close();
        }else{
            Employee prev_employee;
            Employee last_employee= get_s(departmentId_and_EmployeeIdp[employee.departmentCode],employee_id_and_numberRecord);
            while (prev_employee.nextEmployee != employee.id) {
                prev_employee = last_employee;
                last_employee = get_s(last_employee.nextEmployee, employee_id_and_numberRecord);
                if (last_employee.nextEmployee==-1) {
                    break;
                }
            }
            prev_employee.nextEmployee = employee.nextEmployee;
            update_s(prev_employee, prev_employee.departmentCode, employee_id_and_numberRecord, departmentId_and_EmployeeIdp, department_id_and_numberRecord, deletedEmployee);
            
            employee.toDelete=true;
            std::streamoff offset = static_cast<std::streamoff>(employee_id_and_numberRecord[employee.id]) * sizeof(Employee);
            employee_file.seekg(offset);
            
            employee_file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
            employee_file.close();
        }
        
        deletedEmployee[employee.id] = employee_id_and_numberRecord[employee.id];
        employee_id_and_numberRecord.erase(employee.id);
        
        return true;
        //throw std::runtime_error("Faild write deleting record in employee_file");
        
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return false;
}

bool update_m(Department& department,std::map<int,int> &department_id_and_numberRecord){
    try {
        std::fstream department_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Department.dat", std::ios::binary | std::ios::in |std::ios::out);
        if (!department_file.is_open()) {
            throw std::runtime_error("Failed open department_file /update_m \n");
        }
        std::streamoff offset = static_cast<std::streamoff>(department_id_and_numberRecord[department.id]-1) * sizeof(Department);
        department_file.seekp(offset);
        
        department_file.write(reinterpret_cast<char*>(&department), sizeof(Department));
        if (department_file.fail()) {
            throw std::runtime_error("Faild write department_file /update_m ");
        }
        return true;
        
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return false;
}
bool update_s(Employee& employee,int prevDepartmentCode,std::map<int,int> &employee_id_and_numberRecord,std::map<int,int> &departmentId_and_EmployeeIdp,std::map<int,int> &department_id_and_numberRecord,std::map<int, int>& deletedEmployee){
    try {
    std::cout<<'\n'<<"Prev depCode: "<<prevDepartmentCode<<'\n'<<"departmentId_and_EmployeeIdp: "<<departmentId_and_EmployeeIdp[prevDepartmentCode]<<'\n';
        Employee employee_test = get_s(employee.id, employee_id_and_numberRecord);
        
        std::fstream employee_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Employee.dat", std::ios::binary | std::ios::in |std::ios::out);
        if(!employee_file.is_open()){
            employee_file.close();
            throw std::runtime_error("Failde open employee.dat /get_s");
        }
        
        if (employee.departmentCode == prevDepartmentCode) {
            std::cout<<"LOX\n";
            
            std::fstream employee_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Employee.dat", std::ios::binary | std::ios::in |std::ios::out);
            if(!employee_file.is_open()){
                throw std::runtime_error("Failde open employee.dat /get_s");
            }
            if (employee.id > 1) {
                std::streamoff offset = (static_cast<std::streamoff>(employee_id_and_numberRecord[employee.id]) * sizeof(Employee));
                employee_file.seekp(offset);
            }
            if(!employee_file.write(reinterpret_cast<char*>(&employee), sizeof(Employee))){
                throw std::runtime_error("Fail write update record in employee_file /update_s");
            }
            employee_file.close();
        }
        
        
        if (employee_test.nextEmployee==-1) {
            departmentId_and_EmployeeIdp[prevDepartmentCode]=-1;
        }else if(employee.id==employee_test.id){
            departmentId_and_EmployeeIdp[prevDepartmentCode] = employee_test.nextEmployee;
        }else{
            Employee prev_employee;
            while (employee_test.id!=employee.id) {
                prev_employee= employee_test;
                employee_test = get_s(employee_test.nextEmployee, employee_id_and_numberRecord);
            }
            prev_employee.nextEmployee = employee_test.nextEmployee;
            
            std::streamoff offset = static_cast<std::streamoff>(employee_id_and_numberRecord[prev_employee.id]) * sizeof(Employee);
            employee_file.seekg(offset);
            employee_file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
        }
        
        if (departmentId_and_EmployeeIdp[employee.departmentCode]==-1) {
            departmentId_and_EmployeeIdp[employee.departmentCode]=employee.id;
        }else {
            Employee last_employee = get_s(departmentId_and_EmployeeIdp[employee.departmentCode], employee_id_and_numberRecord);
            while (last_employee.nextEmployee!=-1) {
                last_employee = get_s(last_employee.nextEmployee, employee_id_and_numberRecord);
            }
            last_employee.nextEmployee = employee.id;
            
            std::streamoff offset = static_cast<std::streamoff>(employee_id_and_numberRecord[employee.id]) * sizeof(Employee)/*-sizeof(Employee)*/;
            employee_file.seekg(offset);
            employee_file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
        }
        
        employee_file.close();
        return true;
    } catch (std::runtime_error& e) {
        std::cerr<<"An exception occurred: "<<e.what();
    }
    
    return false;
}
//
int calc_m(std::map<int,int> &department_id_and_numberRecord){
    try {
        std::ifstream department_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Department.dat", std::ios::binary);
        if (!department_file.is_open()) {
            department_file.close();
            throw std::runtime_error("Faild open department_file /calc_m");
        }
        
        Department department_buffer;
        int count=0;
        
        while (department_file.read(reinterpret_cast<char*>(&department_buffer), sizeof(Department))) {
            
            if (!department_buffer.toDelete) {
                count++;
            }

        }
        department_file.close();
        return count;
    } catch (std::runtime_error&e ) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    
    return -1;
}
int calc_s(){
    try {
        std::ifstream employee_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Employee.dat", std::ios::binary);
        if (!employee_file.is_open()) {
            throw std::runtime_error("Faild open employee_file /calc_s");
        }
        
        Employee employee_buffer;
        int count;
        
        while (employee_file.read(reinterpret_cast<char*>(&employee_buffer), sizeof(Employee))) {
            if (!employee_buffer.toDelete) {
                count++;
            }
        }
        employee_file.close();
        return count;
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return -1;
}

std::vector<Department> ut_m(){
    std::vector<Department> departments;
    try {
        std::ifstream department_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Department.dat", std::ios::binary);
        if (!department_file.is_open()) {
            throw std::runtime_error("Faild open department_file /ut_m");
        }
        
        Department department_buffer;
        while (department_file.read(reinterpret_cast<char*>(&department_buffer), sizeof(Department))) {
//            if (!department_buffer.toDelete) {
                departments.push_back(department_buffer);
           // }
        }
        
        return departments;
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return departments;
}
std::vector<Employee> ut_s(){
    std::vector<Employee> employees;
    try {
        std::ifstream employee_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Employee.dat", std::ios::binary);
        if (!employee_file.is_open()) {
            throw std::runtime_error("Faild open employee_file /ut_s");
        }
        
        Employee employee_buffer;
        
        while (employee_file.read(reinterpret_cast<char*>(&employee_buffer), sizeof(Employee))) {
            //if (!employee_buffer.toDelete) {
                employees.push_back(employee_buffer);
            //}
        }
        
        return employees;
        
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return employees;
}

void print_Departments(std::vector<Department>& departments){
    for (Department department : departments) {
        std::cout<<"///////////////////////////////////////\n";
        std::cout<<"Id: "<<department.id<<'\n';
        std::cout<<"Name of department: "<<department.fullName<<'\n';
        std::cout<<"Number of employee: "<<department.numberOfEmployee<<'\n';
        std::cout<<"To delete: "<<department.toDelete<<'\n';
    }
    std::cout<<"///////////////////////////////////////\n";
}
void print_Employees(std::vector<Employee>& employees){
    for(Employee employee : employees){
        std::cout<<"///////////////////////////////////////\n";
        std::cout<<"Id: "<<employee.id<<'\n';
        std::cout<<"Full name: "<<employee.fullName<<'\n';
        std::cout<<"Position: "<<employee.position<<'\n';
        std::cout<<"To delete: "<<employee.toDelete<<'\n';
        std::cout<<"Next in this Department: "<<employee.nextEmployee<<'\n';
    }
    std::cout<<"///////////////////////////////////////\n";
}

void print_Department(Department& department){
    std::cout<<"///////////////////////////////////////\n";
    std::cout<<"Id: "<<department.id<<'\n';
    std::cout<<"Name of department: "<<department.fullName<<'\n';
    std::cout<<"Number of employee: "<<department.numberOfEmployee<<'\n';
    std::cout<<"To delete: "<<department.toDelete<<'\n';
    std::cout<<"///////////////////////////////////////\n";
}
void print_Employee(Employee& employee){
    std::cout<<"///////////////////////////////////////\n";
    std::cout<<"Id: "<<employee.id<<'\n';
    std::cout<<"Full name: "<<employee.fullName<<'\n';
    std::cout<<"Position: "<<employee.position<<'\n';
    std::cout<<"To delete: "<<employee.toDelete<<'\n';
    std::cout<<"Next in this Department: "<<employee.nextEmployee<<'\n';
    std::cout<<"///////////////////////////////////////\n";
}


void deleteALL_Data(){
    std::ofstream file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Department.dat", std::ios::binary | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
    std::ofstream file1("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Employee.dat", std::ios::binary | std::ios::trunc);
        if (!file1.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
    std::ofstream file2("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/deletedDepartment.dat", std::ios::binary | std::ios::trunc);
        if (!file2.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
    std::ofstream file3("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/deletedEmployee.dat", std::ios::binary | std::ios::trunc);
        if (!file3.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
    std::ofstream file4("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/department_id_and_numberRecord.dat", std::ios::binary | std::ios::trunc);
        if (!file4.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
    std::ofstream file5("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/departmentId_and_EmployeeId.dat", std::ios::binary | std::ios::trunc);
        if (!file5.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
    std::ofstream file6("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/employee_id_and_numberRecord.dat", std::ios::binary | std::ios::trunc);
        if (!file6.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }

        file.close();
        file1.close();
        file2.close();
        file3.close();
        file4.close();
        file5.close();
        file6.close();


        std::cout << "All data removed from the file." << std::endl;
}



std::map<int, int> readMapFromFile(const std::string& filename){
    std::map<int, int> result_map;
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return result_map;
        }
        
        int key, value;
        while (file >> key >> value) {
            result_map[key] = value;
        }
        
        file.close();
        return result_map;
}


void writeMapToFile(const std::map<int, int>& input_map, const std::string& filename){
    std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        for (const auto& pair : input_map) {
            file << pair.first << " " << pair.second << std::endl;
        }

        file.close();
}

bool isInteger(const std::string& s) {
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
    
    char* p;
    strtol(s.c_str(), &p, 10);
    
    return (*p == 0);
}
template<size_t N>
void readConsoleInput(char (&input)[N]) {
    std::cout << "Enter input: " << std::flush;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.getline(input, N);
}

void findDeletedRecords(std::map<int,int>& deletedEmployee,std::map<int,int>& deletedDerpartment){
    std::ifstream employee_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Employee.dat", std::ios::binary);
    std::ifstream department_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/Department.dat", std::ios::binary);
    
    if (!employee_file.is_open()) {
        std::cerr<<"Faild open employee file in /findDeletedRecords \n";
    }
    if (!department_file.is_open()) {
        std::cerr<<"Faild open department file in /findDeletedRecords \n";
    }
    
    Department department_buffer;
    while (department_file.read(reinterpret_cast<char*>(&department_buffer), sizeof(Department))) {
        if (department_buffer.toDelete) {
            int numberRecord = department_file.tellg()/sizeof(Department);
            //deletedDerpartment.insert(department_buffer.id,numberRecord);
        }
    }
    
    Employee employee_buffer;
    while (employee_file.read(reinterpret_cast<char*>(&employee_buffer), sizeof(Employee))) {
        if (employee_buffer.toDelete) {
            int numberRecord  = employee_file.tellg()/sizeof(Employee)-1;
            //deletedEmployee.insert(employee_buffer.id,numberRecord);
        }
    }
    
}

std::vector<Employee> printAllEmployeeInThisDepartment(Department department,std::map<int, int>& departmentId_and_EmployeeId,std::map<int,int>& employee_id_and_numberRecord){
    
    std::vector<Employee>employees;
    
    Employee employee = get_s(departmentId_and_EmployeeId[department.id], employee_id_and_numberRecord);
    employees.push_back(employee);
    
    Employee prev_employee;
    Employee last_employee= get_s(employee.nextEmployee, employee_id_and_numberRecord);
    employees.push_back(last_employee);
    while (prev_employee.nextEmployee != -1) {
        prev_employee = last_employee;
        last_employee = get_s(last_employee.nextEmployee, employee_id_and_numberRecord);
        employees.push_back(prev_employee);
    }
    employees.push_back(last_employee);
    print_Employees(employees);
    return employees;
}
