//
//  main.cpp
//  Лаба 1 версия 3.0(тест на исправление)
//  Created by Илья Гончаренко on 13.02.2023.
//
#include "Function.hpp"
int _stateMenu;
void Menu(){
    cout<<"Operations: "<<endl
        <<"(0) End program\n"
        <<"(1) data input\n"
        <<"(2) data output\n"
        <<"(3) data output\n"
        <<"(4) deleting a specific element\n"
        <<"(5) deleting all data\n"
        <<"(6) saving\n"
        <<"(7) read\n"
        <<"You choise ";
    cin>> _stateMenu;
}

int main() {
    

    Menu();
    //data initialization
    int amountOfDataS = 0;
    int amountOfDataT = 0;
    
    
    
    
    
    
    teachers* t = new teachers[amountOfDataS];
    student* s = new student [amountOfDataT];
    
    

    while(_stateMenu != 0){
    switch (_stateMenu) {
        case 1:
                cout<<"Student(1) or teacher(2)?\n";
                
                int choise0;
                cin>>choise0;
                
                if(choise0==1){
                    AddDateStudent(s, amountOfDataS);
                    amountOfDataS++;
                }
                else if(choise0==2 ){
                    AddDateTeachers(t, amountOfDataT);
                    amountOfDataT++;
                }
                else cout<<"Operation now founded!";
                
                Menu();
                
                break;
                
                
        case 2:
               
                cout<<"Student(1) or teacher(2)?\n";
                
                int choise1;
                cin>>choise1;
                
                if(choise1==1 && amountOfDataS != 0)
                    PrintStudent(s, amountOfDataS);
                else if(choise1==2 && amountOfDataT != 0)
                    PrintTeachers(t, amountOfDataT);
                else cout<<"Operation now founded!";
                
                Menu();
                
                break;
        case 3:
             
                cout<<"Student(1) or teacher(2)?\n";
                
                int choise2;
                cin>>choise2;
                
                if(choise2==1 && amountOfDataS != 0)
                    DataChangeStudent(s, amountOfDataS);
                else if(choise2==2 && amountOfDataT != 0)
                    DataChangeTeachers(t, amountOfDataT);
                else cout<<"Operation now founded!";
                
                Menu();
                
                break;
        case 4:
             
                cout<<"Student(1) or teacher(2)?\n";
                
                int choise3;
                cin>>choise3;
                
                if(choise3==1 && amountOfDataS != 0)
                    DeleteDataStudent(s, amountOfDataS);
                else if(choise3==2 && amountOfDataT != 0)
                    DeleteDataTeahers(t, amountOfDataT);
                else cout<<"Operation now founded!";
                
                Menu();
                
                break;
        case 5:
                cout<<"Student(1) or teacher(2) or all(3)?\n";
                int deletechoise;
                cin>>deletechoise;
                switch (deletechoise) {
                        
                    case 1:
                        amountOfDataS=0;
                        delete []s;
                        break;
                        
                    case 2:
                        amountOfDataT=0;
                        delete[]t;
                        break;
                        
                    case 3:
                        amountOfDataS=0;
                        delete[]s;
                        amountOfDataT=0;
                        delete[]t;
                        break;
                        
                        
                    default:
                        cout<<"Operation now founded!";
                        break;
            
                }
        case 6:
                cout<<"Student(1) or teacher(2) or all(3)?\n";
                int savechoise;
                cin>>savechoise;
                switch (savechoise) {
                    case 1:
                        SaveDataStudent(s, amountOfDataS);
                        Menu();
                        break;
                    case 2:
                        SaveDataTeachers(t, amountOfDataT);
                        Menu();
                        break;
                    case 3:
                        SaveDataStudent(s, amountOfDataS);
                        SaveDataTeachers(t, amountOfDataT);
                        Menu();
                        break;
                    default:
                        cout<<"not founded!\n";
                        break;
                }
                    
                    break;
        case 7:
                cout<<"Student(1) or teacher(2) or all(3)?\n";
                int readchoise;
                cin>>readchoise;
                switch (readchoise) {
                    case 1:
                        ReadDataStudent(s, amountOfDataS);
                        Menu();
                        break;
                    case 2:
                        ReadDataTeachers(t, amountOfDataT);
                        Menu();
                        break;
                    case 3:
                        cout<<"Student: \n";
                        ReadDataStudent(s, amountOfDataS);
                        cout<<"Teachers: \n";
                        ReadDataTeachers(t, amountOfDataT);
                        Menu();
                        break;
                    default:
                        cout<<"not founded\n";
                        break;
                }
                    
                    break;
               
        default:
                cout<<"Operations not founded!"<<endl;
                break;
        }
    }

    SaveDataStudent(s, amountOfDataS);
    SaveDataTeachers(t, amountOfDataT);
    return 0;
}
