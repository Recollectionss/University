//
//  main.cpp
//  DataBase-lab1
//


#include <iostream>


#include "Function.hpp"


int main(int argc, const char * argv[]) {

    std::map<int,int> ConcertHallId_and_StaffId = readMapFromFile("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHallId_and_StaffId.dat");
    std::map<int,int> ConcertHall_id_and_numberRecord = readMapFromFile("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall_id_and_numberRecord.dat");
    std::map<int,int> Staff_id_and_numberRecord = readMapFromFile("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff_id_and_numberRecord.dat");

    std::map<int,int> deletedConcertHall;
    std::map<int, int> deletedStaff;
    
    std::cout << "Hello, World!\n";
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
                writeMapToFile(ConcertHallId_and_StaffId, "/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHallId_and_StaffId.dat");
                writeMapToFile(ConcertHall_id_and_numberRecord, "/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall_id_and_numberRecord.dat");
                writeMapToFile(Staff_id_and_numberRecord, "/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff_id_and_numberRecord.dat");
                return 0;
                
            case 1:{ //get_m
                std::cout<<"Print id wich found: ";
                int id_for_get_ConcertHall;
                std::cin>>id_for_get_ConcertHall;
                ConcertHall ConcertHall_to_get = get_m(id_for_get_ConcertHall, ConcertHall_id_and_numberRecord);
                print_ConcertHall(ConcertHall_to_get);
                break;
            }
                
            case 2:{ //get_s
                std::cout<<"Print id wich found: ";
                int id_for_get_Staff;
                std::cin>>id_for_get_Staff;
                Staff Staff_to_get = get_s(id_for_get_Staff, Staff_id_and_numberRecord);
                print_Staff(Staff_to_get);
                break;
            }
                
            case 3:{ //insert_m
                ConcertHall ConcertHall_to_insert = create_ConcertHall(ConcertHall_id_and_numberRecord, ConcertHallId_and_StaffId);
                insert_m(ConcertHall_to_insert, ConcertHall_id_and_numberRecord, deletedConcertHall);
                break;
            }
                
            case 4: {//insert_s
                Staff Staff_to_insert = create_Staff(Staff_id_and_numberRecord, ConcertHall_id_and_numberRecord);
                insert_s(Staff_to_insert, Staff_id_and_numberRecord, ConcertHallId_and_StaffId, deletedStaff, ConcertHall_id_and_numberRecord);
                break;
            }
                
            case 5:{ //update_m
                std::cout<<"Write id of ConcertHall for update information \n";
                int id_for_update;
                std::cin>>id_for_update;
                ConcertHall before_update_ConcertHall = get_m(id_for_update, ConcertHall_id_and_numberRecord);
                std::cout<<"Update info before ConcertHall \n";
                print_ConcertHall(before_update_ConcertHall);
                before_update_ConcertHall = create_ConcertHall(ConcertHall_id_and_numberRecord, ConcertHallId_and_StaffId,before_update_ConcertHall);
                update_m(before_update_ConcertHall, ConcertHall_id_and_numberRecord);
                std::cout<<"New info \n";
                print_ConcertHall(before_update_ConcertHall);
                break;
            }
            case 6:{//update_s
                std::cout<<"Write id of Staff for update information \n";
                int id_for_update;
                std::cin>>id_for_update;
                Staff before_update_Staff = get_s(id_for_update, Staff_id_and_numberRecord);
                int prevCode = before_update_Staff.ConcertHallCode;
                std::cout<<"Update info before Staff\n";
                print_Staff(before_update_Staff);
                int next = before_update_Staff.nextStaff;
                before_update_Staff = create_Staff(Staff_id_and_numberRecord, ConcertHall_id_and_numberRecord,before_update_Staff);
                before_update_Staff.nextStaff=next;
                update_s(before_update_Staff, prevCode, Staff_id_and_numberRecord, ConcertHallId_and_StaffId, ConcertHall_id_and_numberRecord, deletedStaff);
                std::cout<<"New info \n";
                print_Staff(before_update_Staff);
                
                break;
            }
            case 7:{ //del_m
                std::cout<<"Write id of ConcertHall for delete information \n";
                int id_for_delete;
                std::cin>>id_for_delete;
                delete_m(id_for_delete, ConcertHall_id_and_numberRecord, deletedConcertHall, ConcertHallId_and_StaffId, Staff_id_and_numberRecord, deletedStaff);
                break;
            }
            case 8:{ //del_s
                std::cout<<"Write id of Staff for delete information \n";
                int id_for_delete;
                std::cin>>id_for_delete;
                delete_s(id_for_delete, Staff_id_and_numberRecord, ConcertHallId_and_StaffId, deletedStaff,ConcertHall_id_and_numberRecord);
                break;
            }
            case 9:{ //calc_m
                int result = calc_m(ConcertHall_id_and_numberRecord);
                std::cout<<"ConcertHalls count record: "<<result<<'\n';
                break;
            }
            case 10:{ //calc_s
                int result = calc_s();
                std::cout<<"Staffs count record: "<<result<<'\n';
                break;
            }
            case 11:{ //ut_m
                std::vector<ConcertHall> ConcertHalls = ut_m();
                print_ConcertHalls(ConcertHalls);
                break;
            }
            case 12:{ //ut_s
                std::vector<Staff> Staffs = ut_s();
                print_Staffs(Staffs);
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
