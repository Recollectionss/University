//
//  Function.cpp
//  DataBase-lab1
//

#include "Function.hpp"
#include <ctime>

ConcertHall create_ConcertHall(std::map<int,int>& ConcertHall_id_and_numberRecord, std::map<int,int>& ConcertHallId_and_StaffIdp,ConcertHall d) {
    ConcertHall ConcertHall;

    std::cout << "Enter ConcertHall full name: ";
    std::cin >> ConcertHall.fullName;
    
    std::cout << "Enter ConcertHall address: ";
    std::cin >> ConcertHall.address;

    std::cout << "Enter floor (>1): ";
    while (!(std::cin >> ConcertHall.floor) || ConcertHall.floor < 1) {
        std::cout << "Invalid input. Please enter a floor greater than or equal to 1." << std::endl;
        std::cout << "Enter floor (>1): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter number of seats (>1): ";
    while (!(std::cin >> ConcertHall.countOfSeets) || ConcertHall.countOfSeets < 1) {
        std::cout << "Invalid input. Please enter a count of seats greater than or equal to 1." << std::endl;
        std::cout << "Enter number of seats (>1): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter number of Staffs (>1): ";
    while (!(std::cin >> ConcertHall.numberOfStaff) || ConcertHall.numberOfStaff < 1) {
        std::cout << "Invalid input. Please enter a number of staff greater than or equal to 1." << std::endl;
        std::cout << "Enter number of Staffs (>1): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (d.id == 0) {
        ConcertHall.id = ConcertHall_id_and_numberRecord.size() + 1;
    } else {
        ConcertHall.id = d.id;
    }

    ConcertHallId_and_StaffIdp[ConcertHall.id] = -1;
    ConcertHall.toDelete = false;

    return ConcertHall;
}



Staff create_Staff(std::map<int,int>& Staff_id_and_numberRecord, std::map<int,int>& ConcertHall_id_and_numberRecord,Staff e) {
    Staff Staff;
    std::string input;
    
    std::cout << "Enter Staff full name: ";
    readConsoleInput(Staff.fullName);
    
    std::cout << "Enter position: ";
    readConsoleInput(Staff.position);
    
    do {
        std::cout << "Enter the age: ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!isInteger(input) || std::stoi(input) < 0);
    Staff.age = std::stoi(input);
    
    int sex;
    do {
        std::cout << "Enter the sex (0 for female, 1 for male): ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (input == "0" || input == "1") {
            sex = std::stoi(input);
        } else {
            std::cout << "Invalid input. Please enter 0 for female or 1 for male." << std::endl;
            continue; // Пропускаем оставшуюся часть цикла и начинаем новую итерацию
        }
    } while (sex != 0 && sex != 1);
    Staff.sex = sex;
    
    do {
        std::cout << "Enter the ConcertHall Code: ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!isInteger(input) || std::stoi(input) <= 0 || get_m(std::stoi(input), ConcertHall_id_and_numberRecord).id == 0);
    
    Staff.ConcertHallCode = std::stoi(input);
    if (e.id==0) {
        Staff.id = Staff_id_and_numberRecord.size() + 1;
    }else{
        Staff.id = e.id;
    }
    Staff_id_and_numberRecord[Staff.id]=-1;
    Staff.toDelete = false;
    
    return Staff;
}

ConcertHall get_m(int id,std::map<int,int> &ConcertHall_id_and_numberRecord){
    try {
        std::ifstream ConcertHall_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall.dat", std::ios::binary);
        if (!ConcertHall_file.is_open()) {
            throw std::runtime_error("Faild open ConcertHall_file /get_m");
        }
        
        
        
        std::streamoff offset = (static_cast<std::streamoff>(ConcertHall_id_and_numberRecord[id]-1 ) * sizeof(ConcertHall))/*-sizeof(ConcertHall)*/;
        ConcertHall_file.seekg(offset);
        
        
        ConcertHall ConcertHall;
        if (!ConcertHall_file.read(reinterpret_cast<char*>(&ConcertHall), sizeof(ConcertHall))) {
                    throw std::runtime_error("Failed to read from ConcertHall_file /get_m");
                }
        
        if (ConcertHall.id!=id) {
            std::cout<<ConcertHall.id<<'\n'<<'\n';
            throw std::runtime_error("Something wrong with read /get_m");
        }
        
        return ConcertHall;
        
    }catch(std::runtime_error& e){
        std::cerr<<"An exception occurred: "<<e.what()<<'\n';
    }
    return {0};
}
Staff get_s(int id,std::map<int,int> &Staff_id_and_numberRecord){
    try {
        auto it = Staff_id_and_numberRecord.rbegin();
        std::cout<<"RBEGIN: "<<it->first<<'\n';
        if (id > it->first) {
            return {-1};
        }
        
        std::ifstream Staff_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff.dat",std::ios::binary);
        if(!Staff_file.is_open()){
            Staff_file.close();
            throw std::runtime_error("Failde open Staff.dat /get_s");
        }
        //if (id!=1) {
            std::streamoff offset = static_cast<std::streamoff>(Staff_id_and_numberRecord[id]) * sizeof(Staff);
            Staff_file.seekg(offset);
       // }
        
        Staff Staff;
        if (!Staff_file.read(reinterpret_cast<char*>(&Staff), sizeof(Staff))) {
            Staff_file.close();
            throw std::runtime_error("Faild read from Staff_file /get_s");
        }
       
        Staff_file.close();
        return Staff;
    } catch (std::runtime_error& e) {
        std::cerr<<"An exception occurred: "<<e.what();
        
    }
    return {-2};
}

bool insert_m(ConcertHall& ConcertHall,std::map<int,int>& ConcertHall_id_and_numberRecord,std::map<int,int> & deletedConcertHall){
    try{
        std::fstream ConcertHall_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall.dat",std::ios::binary | std::ios::in |std::ios::out);
        if (!ConcertHall_file.is_open()) {
            ConcertHall_file.close();
            throw std::runtime_error("Failed open ConcertHall_file /insert_m");
        }
        
        if (!deletedConcertHall.empty()) {
            auto it = deletedConcertHall.begin();
            std::streamoff offset = static_cast<std::streamoff>(it->second)* sizeof(ConcertHall);
            ConcertHall_file.seekg(offset);
            deletedConcertHall.erase(it);
        }else   {
            ConcertHall_file.close();
            std::ofstream ConcertHall_file_f("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall.dat",std::ios::binary | std::ios::app);
            ConcertHall_file_f.write(reinterpret_cast<char*>(&ConcertHall), sizeof(ConcertHall));
            ConcertHall_id_and_numberRecord[ConcertHall.id] = ConcertHall_file_f.tellp()/sizeof(ConcertHall);
        }
        ConcertHall_file.close();
        return true;
        
    }catch(std::runtime_error& e){
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return false;
}
bool insert_s(Staff& Staff,std::map<int,int> &Staff_id_and_numberRecord,std::map<int,int> &ConcertHallId_and_StaffIdp,std::map<int,int>& deletedStaff,std::map<int,int> &ConcertHall_id_and_numberRecord){

    try {
            std::fstream Staff_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff.dat",std::ios::binary | std::ios::in |std::ios::out);
            if (!Staff_file.is_open()) {
                Staff_file.close();
                throw std::runtime_error("Failed open Staff_file /insert_s");
            }
        
            if (!deletedStaff.empty()) {
                auto it = deletedStaff.begin();
                std::streamoff offset = static_cast<std::streamoff>(it->second) * sizeof(Staff);
                Staff_file.seekg(offset);
                deletedStaff.erase(it);
            }
                
                Staff_file.close();
                std::ofstream Staff_file_write("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff.dat",std::ios::binary | std::ios::app );
                
                //        Staff_file_write.write(reinterpret_cast<char*>(&Staff), sizeof(Staff));
                
                
                if (ConcertHallId_and_StaffIdp[Staff.ConcertHallCode]== -1) {
                    ConcertHallId_and_StaffIdp[Staff.ConcertHallCode]=Staff.id;
                }else{
            
                    struct Staff last_Staff = get_s(ConcertHallId_and_StaffIdp[Staff.ConcertHallCode], Staff_id_and_numberRecord);
                    while (last_Staff.nextStaff!= -1) {
                        last_Staff = get_s(last_Staff.nextStaff, Staff_id_and_numberRecord);
                    }
                    last_Staff.nextStaff=Staff.id;
                    update_s(last_Staff, last_Staff.ConcertHallCode, Staff_id_and_numberRecord, ConcertHallId_and_StaffIdp, ConcertHall_id_and_numberRecord, deletedStaff);
            
                    int numberRecord = Staff_file_write.tellp()/sizeof(Staff);
                    Staff_id_and_numberRecord[Staff.id] = numberRecord;
                    Staff_file_write.write(reinterpret_cast<char*>(&Staff), sizeof(Staff));
                    Staff_file.close();
                    return true;
                }
        int numberRecord = Staff_file_write.tellp()/sizeof(Staff)/*-sizeof(Staff)*/;
        Staff_id_and_numberRecord[Staff.id] = numberRecord;
        Staff_file_write.write(reinterpret_cast<char*>(&Staff), sizeof(Staff));
        Staff_file.close();
                return true;
            
            
    } catch (std::runtime_error& e) {
           std::cerr<<"An exeption occured: "<<e.what()<<'\n';
       }
       return false;
}
//
bool delete_m(int id,std::map<int,int> &ConcertHall_id_and_numberRecord,std::map<int,int> &deletedConcertHall,std::map<int,int> &ConcertHallId_and_StaffIdp,std::map<int,int> &Staff_id_and_numberRecord,std::map<int,int>& deletedStaff){
    try {
        std::fstream ConcertHall_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall.dat", std::ios::binary | std::ios::in |std::ios::out);
        if (!ConcertHall_file.is_open()) {
            throw std::runtime_error("Failed open ConcertHall_file /delete_m ");
        }
        
        
        ConcertHall ConcertHall;
        ConcertHall = get_m(id,ConcertHall_id_and_numberRecord);
        ConcertHall.toDelete=true;
        

        std::streamoff offset = static_cast<std::streamoff>(ConcertHall_id_and_numberRecord[id] - 1) * sizeof(ConcertHall);
        ConcertHall_file.seekg(offset);
        
        ConcertHall_file.write(reinterpret_cast<char*>(&ConcertHall), sizeof(ConcertHall));
        if (ConcertHall_file.fail()) {
            throw std::runtime_error("Faild write ConcertHall_file /delete_m ");
        }
        
        //std::cout<<"Staff ID VALUE: "<<ConcertHallId_and_StaffIdp[ConcertHall.id]<<'\n';
        
        if (ConcertHallId_and_StaffIdp[ConcertHall.id]!= -1) {
            Staff last_Staff = get_s(ConcertHallId_and_StaffIdp[ConcertHall.id], Staff_id_and_numberRecord);
            if (last_Staff.nextStaff != -1) {
                while (last_Staff.nextStaff != -1) {
                    delete_s(last_Staff.id, Staff_id_and_numberRecord, ConcertHallId_and_StaffIdp, deletedStaff,ConcertHall_id_and_numberRecord);
                    last_Staff = get_s(last_Staff.nextStaff, Staff_id_and_numberRecord);
                }
            }
            delete_s(last_Staff.id, Staff_id_and_numberRecord, ConcertHallId_and_StaffIdp, deletedStaff,ConcertHall_id_and_numberRecord);
        }
        
        ConcertHallId_and_StaffIdp.erase(ConcertHall.id);
        
        auto it = ConcertHall_id_and_numberRecord.find(ConcertHall.id);
        deletedConcertHall[it->first]=it->second;
        ConcertHall_id_and_numberRecord.erase(it);
        
        
        
        return true;
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return false;
}
bool delete_s(int id,std::map<int,int>& Staff_id_and_numberRecord,std::map<int,int>& ConcertHallId_and_StaffIdp,std::map<int, int>& deletedStaff,std::map<int,int> &ConcertHall_id_and_numberRecord){
    try {
        std::fstream Staff_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff.dat", std::ios::binary | std::ios::in |std::ios::out );
        if (!Staff_file.is_open()) {
            Staff_file.close();
            throw std::runtime_error("Failed open Staff_file /delete_s ");
        }
        
        
        Staff Staff = get_s(id,Staff_id_and_numberRecord);
        Staff.toDelete = true;
        
        if (ConcertHallId_and_StaffIdp[Staff.ConcertHallCode]==Staff.id) {
            ConcertHallId_and_StaffIdp[Staff.ConcertHallCode] = Staff.nextStaff;
            
            Staff.toDelete=true;
            std::streamoff offset = static_cast<std::streamoff>(Staff_id_and_numberRecord[Staff.id]) * sizeof(Staff);
            Staff_file.seekg(offset);
            
            Staff_file.write(reinterpret_cast<char*>(&Staff), sizeof(Staff));
            Staff_file.close();
        }else{
            struct Staff prev_Staff;
            struct Staff last_Staff= get_s(ConcertHallId_and_StaffIdp[Staff.ConcertHallCode],Staff_id_and_numberRecord);
            while (prev_Staff.nextStaff != Staff.id) {
                prev_Staff = last_Staff;
                last_Staff = get_s(last_Staff.nextStaff, Staff_id_and_numberRecord);
                if (last_Staff.nextStaff==-1) {
                    break;
                }
            }
            prev_Staff.nextStaff = Staff.nextStaff;
            update_s(prev_Staff, prev_Staff.ConcertHallCode, Staff_id_and_numberRecord, ConcertHallId_and_StaffIdp, ConcertHall_id_and_numberRecord, deletedStaff);
            
            Staff.toDelete=true;
            std::streamoff offset = static_cast<std::streamoff>(Staff_id_and_numberRecord[Staff.id]) * sizeof(Staff);
            Staff_file.seekg(offset);
            
            Staff_file.write(reinterpret_cast<char*>(&Staff), sizeof(Staff));
            Staff_file.close();
        }
        
        deletedStaff[Staff.id] = Staff_id_and_numberRecord[Staff.id];
        Staff_id_and_numberRecord.erase(Staff.id);
        
        return true;
        //throw std::runtime_error("Faild write deleting record in Staff_file");
        
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return false;
}

bool update_m(ConcertHall& ConcertHall,std::map<int,int> &ConcertHall_id_and_numberRecord){
    try {
        std::fstream ConcertHall_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall.dat", std::ios::binary | std::ios::in |std::ios::out);
        if (!ConcertHall_file.is_open()) {
            throw std::runtime_error("Failed open ConcertHall_file /update_m \n");
        }
        std::streamoff offset = static_cast<std::streamoff>(ConcertHall_id_and_numberRecord[ConcertHall.id]-1) * sizeof(ConcertHall);
        ConcertHall_file.seekp(offset);
        
        ConcertHall_file.write(reinterpret_cast<char*>(&ConcertHall), sizeof(ConcertHall));
        if (ConcertHall_file.fail()) {
            throw std::runtime_error("Faild write ConcertHall_file /update_m ");
        }
        return true;
        
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return false;
}
bool update_s(Staff& Staff,int prevConcertHallCode,std::map<int,int> &Staff_id_and_numberRecord,std::map<int,int> &ConcertHallId_and_StaffIdp,std::map<int,int> &ConcertHall_id_and_numberRecord,std::map<int, int>& deletedStaff){
    try {
    std::cout<<'\n'<<"Prev depCode: "<<prevConcertHallCode<<'\n'<<"ConcertHallId_and_StaffIdp: "<<ConcertHallId_and_StaffIdp[prevConcertHallCode]<<'\n';
        struct Staff Staff_test = get_s(Staff.id, Staff_id_and_numberRecord);
        
        std::fstream Staff_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff.dat", std::ios::binary | std::ios::in |std::ios::out);
        if(!Staff_file.is_open()){
            Staff_file.close();
            throw std::runtime_error("Failde open Staff.dat /get_s");
        }
        
        if (Staff.ConcertHallCode == prevConcertHallCode) {
            std::cout<<"LOX\n";
            
            std::fstream Staff_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff.dat", std::ios::binary | std::ios::in |std::ios::out);
            if(!Staff_file.is_open()){
                throw std::runtime_error("Failde open Staff.dat /get_s");
            }
            if (Staff.id > 1) {
                std::streamoff offset = (static_cast<std::streamoff>(Staff_id_and_numberRecord[Staff.id]) * sizeof(Staff));
                Staff_file.seekp(offset);
            }
            if(!Staff_file.write(reinterpret_cast<char*>(&Staff), sizeof(Staff))){
                throw std::runtime_error("Fail write update record in Staff_file /update_s");
            }
            Staff_file.close();
        }
        
        
        if (Staff_test.nextStaff==-1) {
            ConcertHallId_and_StaffIdp[prevConcertHallCode]=-1;
        }else if(Staff.id==Staff_test.id){
            ConcertHallId_and_StaffIdp[prevConcertHallCode] = Staff_test.nextStaff;
        }else{
            struct Staff prev_Staff;
            while (Staff_test.id!=Staff.id) {
                prev_Staff= Staff_test;
                Staff_test = get_s(Staff_test.nextStaff, Staff_id_and_numberRecord);
            }
            prev_Staff.nextStaff = Staff_test.nextStaff;
            
            std::streamoff offset = static_cast<std::streamoff>(Staff_id_and_numberRecord[prev_Staff.id]) * sizeof(Staff);
            Staff_file.seekg(offset);
            Staff_file.write(reinterpret_cast<char*>(&Staff), sizeof(Staff));
        }
        
        if (ConcertHallId_and_StaffIdp[Staff.ConcertHallCode]==-1) {
            ConcertHallId_and_StaffIdp[Staff.ConcertHallCode]=Staff.id;
        }else {
            struct Staff last_Staff = get_s(ConcertHallId_and_StaffIdp[Staff.ConcertHallCode], Staff_id_and_numberRecord);
            while (last_Staff.nextStaff!=-1) {
                last_Staff = get_s(last_Staff.nextStaff, Staff_id_and_numberRecord);
            }
            last_Staff.nextStaff = Staff.id;
            
            std::streamoff offset = static_cast<std::streamoff>(Staff_id_and_numberRecord[Staff.id]) * sizeof(Staff)/*-sizeof(Staff)*/;
            Staff_file.seekg(offset);
            Staff_file.write(reinterpret_cast<char*>(&Staff), sizeof(Staff));
        }
        
        Staff_file.close();
        return true;
    } catch (std::runtime_error& e) {
        std::cerr<<"An exception occurred: "<<e.what();
    }
    
    return false;
}
//
int calc_m(std::map<int,int> &ConcertHall_id_and_numberRecord){
    try {
        std::ifstream ConcertHall_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall.dat", std::ios::binary);
        if (!ConcertHall_file.is_open()) {
            ConcertHall_file.close();
            throw std::runtime_error("Faild open ConcertHall_file /calc_m");
        }
        
        ConcertHall ConcertHall_buffer;
        int count=0;
        
        while (ConcertHall_file.read(reinterpret_cast<char*>(&ConcertHall_buffer), sizeof(ConcertHall))) {
            
            if (!ConcertHall_buffer.toDelete) {
                count++;
            }

        }
        ConcertHall_file.close();
        return count;
    } catch (std::runtime_error&e ) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    
    return -1;
}
int calc_s(){
    try {
        std::ifstream Staff_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff.dat", std::ios::binary);
        if (!Staff_file.is_open()) {
            throw std::runtime_error("Faild open Staff_file /calc_s");
        }
        
        Staff Staff_buffer;
        int count;
        
        while (Staff_file.read(reinterpret_cast<char*>(&Staff_buffer), sizeof(Staff))) {
            if (!Staff_buffer.toDelete) {
                count++;
            }
        }
        Staff_file.close();
        return count;
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return -1;
}

std::vector<ConcertHall> ut_m(){
    std::vector<ConcertHall> ConcertHalls;
    try {
        std::ifstream ConcertHall_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall.dat", std::ios::binary);
        if (!ConcertHall_file.is_open()) {
            throw std::runtime_error("Faild open ConcertHall_file /ut_m");
        }
        
        ConcertHall ConcertHall_buffer;
        while (ConcertHall_file.read(reinterpret_cast<char*>(&ConcertHall_buffer), sizeof(ConcertHall))) {
            if (!ConcertHall_buffer.toDelete) {
                ConcertHalls.push_back(ConcertHall_buffer);
            }
        }
        
        return ConcertHalls;
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return ConcertHalls;
}
std::vector<Staff> ut_s(){
    std::vector<Staff> Staffs;
    try {
        std::ifstream Staff_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff.dat", std::ios::binary);
        if (!Staff_file.is_open()) {
            throw std::runtime_error("Faild open Staff_file /ut_s");
        }
        
        Staff Staff_buffer;
        
        while (Staff_file.read(reinterpret_cast<char*>(&Staff_buffer), sizeof(Staff))) {
            if (!Staff_buffer.toDelete) {
                Staffs.push_back(Staff_buffer);
            }
        }
        
        return Staffs;
        
    } catch (std::runtime_error& e) {
        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
    }
    return Staffs;
}

void print_ConcertHalls(std::vector<ConcertHall>& ConcertHalls){
    for (ConcertHall ConcertHall : ConcertHalls) {
        std::cout<<"///////////////////////////////////////\n";
        std::cout<<"Id: "<<ConcertHall.id<<'\n';
        std::cout<<"Name of ConcertHall: "<<ConcertHall.fullName<<'\n';
        std::cout<<"Number of Staff:"<<ConcertHall.numberOfStaff<<'\n';
        std::cout<<"Count of seets: "<<ConcertHall.countOfSeets<<'\n';
        std::cout<<"Number of floor: "<<ConcertHall.floor<<'\n';
        std::cout<<"To delete: "<<ConcertHall.toDelete<<'\n';
    }
    std::cout<<"///////////////////////////////////////\n";
}
void print_Staffs(std::vector<Staff>& Staffs){
    for(Staff Staff : Staffs){
        std::cout<<"///////////////////////////////////////\n";
        std::cout<<"Id: "<<Staff.id<<'\n';
        std::cout<<"Full name: "<<Staff.fullName<<'\n';
        std::cout<<"Position: "<<Staff.position<<'\n';
        std::cout<<"Age: "<<Staff.age<<'\n';
        std::cout<<"Sex: ";
        Staff.sex>0 ? std::cout<<"male \n" : std::cout<<"female \n";
        std::cout<<"To delete: "<<Staff.toDelete<<'\n';
        std::cout<<"Next in this ConcertHall: "<<Staff.nextStaff<<'\n';
        std::cout<<"Concert hall id: "<<Staff.ConcertHallCode<<'\n';
    }
    std::cout<<"///////////////////////////////////////\n";
}

void print_ConcertHall(ConcertHall& ConcertHall){
    std::cout<<"///////////////////////////////////////\n";
    std::cout<<"Id: "<<ConcertHall.id<<'\n';
    std::cout<<"Name of ConcertHall: "<<ConcertHall.fullName<<'\n';
    std::cout<<"Address: "<<ConcertHall.address<<'\n';
    std::cout<<"Number of Staff:"<<ConcertHall.numberOfStaff<<'\n';
    std::cout<<"Count of seets: "<<ConcertHall.countOfSeets<<'\n';
    std::cout<<"Number of floor: "<<ConcertHall.floor<<'\n';
    std::cout<<"To delete: "<<ConcertHall.toDelete<<'\n';
    std::cout<<"///////////////////////////////////////\n";
}
void print_Staff(Staff& Staff){
    std::cout<<"///////////////////////////////////////\n";
    std::cout<<"Id: "<<Staff.id<<'\n';
    std::cout<<"Full name: "<<Staff.fullName<<'\n';
    std::cout<<"Position: "<<Staff.position<<'\n';
    std::cout<<"Age: "<<Staff.age<<'\n';
    std::cout<<"Sex: ";
    Staff.sex>0 ? std::cout<<"male \n" : std::cout<<"female \n";
    std::cout<<"To delete: "<<Staff.toDelete<<'\n';
    std::cout<<"Next in this ConcertHall: "<<Staff.nextStaff<<'\n';
    std::cout<<"Concert hall id: "<<Staff.ConcertHallCode<<'\n';
    std::cout<<"///////////////////////////////////////\n";
}


void deleteALL_Data(){
    std::ofstream file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall.dat", std::ios::binary | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
    std::ofstream file1("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff.dat", std::ios::binary | std::ios::trunc);
        if (!file1.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
    std::ofstream file4("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall_id_and_numberRecord.dat", std::ios::binary | std::ios::trunc);
        if (!file4.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
    std::ofstream file5("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHallId_and_StaffId.dat", std::ios::binary | std::ios::trunc);
        if (!file5.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }
    std::ofstream file6("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff_id_and_numberRecord.dat", std::ios::binary | std::ios::trunc);
        if (!file6.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
        }

        file.close();
        file1.close();
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

void findDeletedRecords(std::map<int,int>& deletedStaff,std::map<int,int>& deletedDerpartment){
    
}


//std::map<int,int> readDeletingConcertHall(){
//    std::map<int,int> deletedConcertHall;
//    
//    std::ifstream ConcertHall_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/ConcertHall.dat", std::ios::binary);
//    if (!ConcertHall_file.is_open()) {
//        throw std::runtime_error("Faild open ConcertHall_file /ut_m");
//    }
//    
//    ConcertHall ConcertHall_buffer;
//    while (ConcertHall_file.read(reinterpret_cast<char*>(&ConcertHall_buffer), sizeof(ConcertHall))) {
//        if (ConcertHall_buffer.toDelete) {
//            int numberRecord = ConcertHall_file.tellg()/sizeof(ConcertHall_file);
//            deletedConcertHall.insert(ConcertHall_buffer.id, numberRecord);
//        }
//    }
//    return deletedConcertHall;
//}
//std::map<int,int> readDeletingStaff(){
//    std::map<int,int> deletingStaff;
//    try {
//        std::ifstream Staff_file("/Users/ilagoncarenko/Downloads/ALL/Институт/Курсы/2 курс/БД/DataBase-lab1 — Vika/DataBase-lab1-Vika/DataBase-lab1-Vika/Staff.dat", std::ios::binary);
//        if (!Staff_file.is_open()) {
//            throw std::runtime_error("Faild open ConcertHall_file /ut_m");
//        }
//        
//        Staff staff_buffer;
//        while (Staff_file.read(reinterpret_cast<char*>(&staff_buffer), sizeof(Staff))) {
//            if (staff_buffer.toDelete) {
//                int numberRecord = Staff_file.tellg()/sizeof(Staff) -1 ;
//                deletingStaff.insert(staff_buffer.id, numberRecord);
//            }
//        }
//        
//        return deletingStaff;
//    } catch (std::runtime_error& e) {
//        std::cerr<<"An exeption occured: "<<e.what()<<'\n';
//    }
//    return deletingStaff;
//}
