//
//  main.cpp
//  DataBase-lab1
//
//  Created by Илья Гончаренко on 22.02.2024.
//

#include <iostream>


#include "Function.hpp"


int main(int argc, const char * argv[]) {

//    // insert code here...
    std::map<int,int> departmentId_and_EmployeeId = readMapFromFile("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/departmentId_and_EmployeeId.dat");
    std::map<int,int> department_id_and_numberRecord = readMapFromFile("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/department_id_and_numberRecord.dat");
    std::map<int,int> employee_id_and_numberRecord = readMapFromFile("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/employee_id_and_numberRecord.dat");
//    std::map<int,int> departmentId_and_EmployeeId ;
//    std::map<int,int> department_id_and_numberRecord ;
//    std::map<int,int> employee_id_and_numberRecord;
    std::map<int,int> deletedDepartment;
    std::map<int, int> deletedEmployee;
    
    findDeletedRecords(deletedEmployee, deletedDepartment);
    
    std::cout << "Hello, World!\n";
    //deleteALL_Data();
    while (true) {
        std::cout<<"0. exit \n";
        std::cout<<"1. get_m \n";
        std::cout<<"2. get_s \n";
        std::cout<<"3. insert_m \n";
        std::cout<<"4. insert_s \n";
        std::cout<<"5. update_m \n";
        std::cout<<"6. update_s \n";
        std::cout<<"7. del_m \n";
        std::cout<<"8. del_s \n";
        std::cout<<"9. calc_m  \n";
        std::cout<<"10. calc_s \n";
        std::cout<<"11. ut_m \n";
        std::cout<<"12. ut_s \n";
        std::cout<<"13. delete all information \n";
        
        int value;
        std::cin>>value;
        
        switch (value){
            case 0:
                writeMapToFile(departmentId_and_EmployeeId, "/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/departmentId_and_EmployeeId.dat");
                writeMapToFile(department_id_and_numberRecord, "/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/department_id_and_numberRecord.dat");
                writeMapToFile(employee_id_and_numberRecord, "/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1/DataBase-lab1/employee_id_and_numberRecord.dat");
                return 0;
                
            case 1:{ //get_m
                std::cout<<"Print id wich found: ";
                int id_for_get_department;
                std::cin>>id_for_get_department;
                Department department_to_get = get_m(id_for_get_department, department_id_and_numberRecord);
                print_Department(department_to_get);
                //std::cout<<"FFFF "<<departmentId_and_EmployeeId[department_to_get.id]<<'\n';
                printAllEmployeeInThisDepartment(department_to_get, departmentId_and_EmployeeId, department_id_and_numberRecord);
                break;
            }
                
            case 2:{ //get_s
                std::cout<<"Print id wich found: ";
                int id_for_get_employee;
                std::cin>>id_for_get_employee;
                Employee employee_to_get = get_s(id_for_get_employee, employee_id_and_numberRecord);
                print_Employee(employee_to_get);
                break;
            }
                
            case 3:{ //insert_m
                Department department_to_insert = create_Department(department_id_and_numberRecord, departmentId_and_EmployeeId);
                insert_m(department_to_insert, department_id_and_numberRecord, deletedDepartment);
                break;
            }
                
            case 4: {//insert_s
                Employee employee_to_insert = create_Employee(employee_id_and_numberRecord, department_id_and_numberRecord);
                insert_s(employee_to_insert, employee_id_and_numberRecord, departmentId_and_EmployeeId, deletedEmployee, department_id_and_numberRecord);
                break;
            }
                
            case 5:{ //update_m
                std::cout<<"Write id of Department for update information \n";
                int id_for_update;
                std::cin>>id_for_update;
                Department before_update_department = get_m(id_for_update, department_id_and_numberRecord);
                std::cout<<"Update info before department \n";
                print_Department(before_update_department);
                before_update_department = create_Department(department_id_and_numberRecord, departmentId_and_EmployeeId,before_update_department);
                update_m(before_update_department, department_id_and_numberRecord);
                std::cout<<"New info \n";
                print_Department(before_update_department);
                break;
            }
            case 6:{//update_s
                std::cout<<"Write id of Employee for update information \n";
                int id_for_update;
                std::cin>>id_for_update;
                Employee before_update_employee = get_s(id_for_update, employee_id_and_numberRecord);
                int prevCode = before_update_employee.departmentCode;
                std::cout<<"Update info before employee\n";
                print_Employee(before_update_employee);
                int next = before_update_employee.nextEmployee;
                before_update_employee = create_Employee(employee_id_and_numberRecord, department_id_and_numberRecord,before_update_employee);
                before_update_employee.nextEmployee=next;
                update_s(before_update_employee, prevCode, employee_id_and_numberRecord, departmentId_and_EmployeeId, department_id_and_numberRecord, deletedEmployee);
                std::cout<<"New info \n";
                print_Employee(before_update_employee);
                
                break;
            }
            case 7:{ //del_m
                std::cout<<"Write id of Department for delete information \n";
                int id_for_delete;
                std::cin>>id_for_delete;
                delete_m(id_for_delete, department_id_and_numberRecord, deletedDepartment, departmentId_and_EmployeeId, employee_id_and_numberRecord, deletedEmployee);
                break;
            }
            case 8:{ //del_s
                std::cout<<"Write id of Employee for delete information \n";
                int id_for_delete;
                std::cin>>id_for_delete;
                delete_s(id_for_delete, employee_id_and_numberRecord, departmentId_and_EmployeeId, deletedEmployee,department_id_and_numberRecord);
                break;
            }
            case 9:{ //calc_m
                int result = calc_m(department_id_and_numberRecord);
                std::cout<<"Departments count record: "<<result<<'\n';
                break;
            }
            case 10:{ //calc_s
                int result = calc_s();
                std::cout<<"Employees count record: "<<result<<'\n';
                break;
            }
            case 11:{ //ut_m
                std::vector<Department> departments = ut_m();
                print_Departments(departments);
                break;
            }
            case 12:{ //ut_s
                std::vector<Employee> employees = ut_s();
                print_Employees(employees);
                break;
            }
            case 13:{ //delete all information
                deleteALL_Data();
            }
            default:
                break;
        }
    }
    return 0;
}
