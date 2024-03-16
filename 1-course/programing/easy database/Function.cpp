//
//  Function.cpp
//  Лаба 1 версия 3.0(тест на исправление)
//
//  Created by Илья Гончаренко on 13.02.2023.
//

#include "Function.hpp"

void AddDateStudent (student* (&s), int &n){
    //temporary data array
    student* buf;
    buf= new student[n];

    //save data to temporary array
    CopyStudent(buf,s,n);

    //allocate new memory
    n++;
    s= new student[n];

    //return data
    CopyStudent(s,buf,--n);
    

  
            cout<<"Введите ФИО: ";
            cin>> s[n].surname;
            cin>> s[n].name;
            cin>> s[n].patronymic;
            cout<<"Группа: ";
            cin>> s[n].group;
            cout<<"Данные изменены!"<<endl;

    delete[]buf;
}


void AddDateTeachers (teachers* (&t), int &n){
    //temporary data array
    teachers* buf;
    buf= new teachers[n];

    //save data to temporary array
    CopyTeachers(buf,t,n);

    //allocate new memory
    n++;
    t= new teachers[n];

    //return data
    CopyTeachers(t,buf,--n);
    

            cout<<"Введите ФИО: ";
            cin>> t[n].surname;
            cin>> t[n].name;
            cin>> t[n].patronymic;
            cout<<"Введите кабинет: ";
            cin>> t[n].cabinet;
            cout<<"Данные изменены!"<<endl;

    delete[]buf;
}



void PrintStudent(student* (&s), int &n){
    for(int i = 0; i < n; i++){
        cout<<"___________________________________"<<endl;
        cout<<"\nData №"<< i+1<<':'<<endl;
        cout<<"Full name: "<<s[i].surname <<' '<< s[i].name<<' '<< s[i].patronymic<<endl;
        cout<<"Group: "<<s[i].group <<endl;
        cout<<"___________________________________"<<endl;
    }
}
void PrintTeachers(teachers* (&t), int &n){
    for(int i = 0; i < n; i++){
        cout<<"___________________________________"<<endl;
        cout<<"\nData №"<< i+1<<':'<<endl;
        cout<<"Full name: "<<t[i].surname <<' '<< t[i].name<<' '<< t[i].patronymic<<endl;
        cout<<"Cabinet: "<<t[i].cabinet <<endl;
        cout<<"___________________________________"<<endl;
    }
}



void DataChangeStudent(student* (&s), int &n){
    int _n;
    cout<< "Enter item number (от 1 до "<<n<<"): ";
    cin>> _n;
    _n--;// because we ask the user to enter from 1 and not from 0
    // check that the correct value was entered
    if(_n> n){
        
    }else{
        
        cout<<"Enter your full name: ";
        cin>> s[_n].surname;
        cin>> s[_n].name;
        cin>> s[_n].patronymic;
        
        cout<<"Group: ";
        cin>> s[_n].group;
        cout<<"Data changed!"<<endl;
    }

}
void DataChangeTeachers(teachers* (&t), int &n){
    int _n;
    cout<< "Enter item number (от 1 до "<<n<<"): ";
    cin>> _n;
    _n--;// because we ask the user to enter from 1 and not from 0
    // check that the correct value was entered
    if(_n> n){
        
    }else{
        cout<<"Enter your full name: ";
        cin>> t[_n].surname;
        cin>> t[_n].name;
        cin>> t[_n].patronymic;
        
        cout<<"Cabinet: ";
        cin>> t[_n].cabinet;
        cout<<"Data changed!"<<endl;
    }

}


void DeleteDataStudent(student* (&s), int &n){
    int _n;
    cout<<"Enter item number (от 1 до"<< n<<"): ";
    cin>> _n;
    _n--;// because we ask the user to enter from 1 and not from 0
    // check that the correct value was entered
    if (_n >= 0 && _n < n){
        //temporary array
        student* buf = new student[n];
        CopyStudent(buf,s,n);
        //allocate new memory
        --n;
        s= new student[n];
        int q = 0;
        //remember data except for unnecessary
        for(int i = 0; i <= n; i++){
            if(i != _n){
                s[q]=buf[i];
                ++q;
            }
        }

        delete[]buf;
        cout<<"Data changed!"<<endl;

    }else
        cout<<"Operation not founded!"<<endl;

}
void DeleteDataTeahers(teachers* (&t), int &n){
    int _n;
    cout<<"Enter item number (от 1 до"<< n<<"): ";
    cin>> _n;
    _n--;// because we ask the user to enter from 1 and not from 0
    // check that the correct value was entered
    if (_n >= 0 && _n < n){
        //temporary array
        teachers* buf = new teachers[n];
        CopyTeachers(buf,t,n);
        //allocate new memory
        --n;
        t= new teachers[n];
        int q = 0;
        //remember data except for unnecessary
        for(int i = 0; i <= n; i++){
            if(i != _n){
                t[q]=buf[i];
                ++q;
            }
        }

        delete[]buf;
        cout<<"Data changed!"<<endl;

    }else
        cout<<"Operation not founded!"<<endl;

}



void CopyStudent(student* (&s_n), student* (&s_o), int n){
    for(int i = 0; i < n; i++){
        s_n[i]=s_o[i];
    }
}
void CopyTeachers(teachers* (&t_n), teachers* (&t_o), int n){
    for(int i = 0; i < n; i++){
        t_n[i]=t_o[i];
    }
}


void SaveDataStudent(student* &s, int &n) {
    // saving the number of records
    ofstream filenumber("/Users/ilagoncarenko/Downloads/Практики /Лаба 1 версия 3.0(тест на исправление)/Лаба 1 версия 3.0(тест на исправление)/NumberStudent.txt");
    if (!filenumber) {
        cout << "Error opening NumberStudent.txt file\n";
        return;
    }
    filenumber << n;
    filenumber.close();

    // saving data
    ofstream fout("/Users/ilagoncarenko/Downloads/Практики /Лаба 1 версия 3.0(тест на исправление)/Лаба 1 версия 3.0(тест на исправление)/student.txt", ios::binary);
    if (!fout) {
        cout << "Error opening persons1.txt file\n";
        return;
    }
    fout.write((char*)s, sizeof(student)*n);
    fout.close();

}

void SaveDataTeachers(teachers* &t, int &n)
{
    // saving the number of records
    ofstream filenumber("/Users/ilagoncarenko/Downloads/Практики /Лаба 1 версия 3.0(тест на исправление)/Лаба 1 версия 3.0(тест на исправление)/NumberTeachers.txt", ios::binary);
    if (!filenumber) {
        cout << "Error opening NumberTeachers.txt file\n";
        return;
    }
    filenumber << n;
    filenumber.close();

    // saving data
    ofstream fout("/Users/ilagoncarenko/Downloads/Практики /Лаба 1 версия 3.0(тест на исправление)/Лаба 1 версия 3.0(тест на исправление)/teachers.txt", ios::binary);
    if (!fout) {
        cout << "Error opening persons1.txt file\n";
        return;
    }
    fout.write((char*)t, sizeof(teachers)*n);
    fout.close();

}

void ReadDataStudent(student* &s, int& n) {
    // read number of records
    ifstream filenumber("/Users/ilagoncarenko/Downloads/Практики /Лаба 1 версия 3.0(тест на исправление)/Лаба 1 версия 3.0(тест на исправление)/NumberStudent.txt", ios::binary);
    if (!filenumber) {
        cout << "Error opening NumberStudent.txt file\n";
        return;
    }
    filenumber >> n;
    filenumber.close();

    // memory allocation for an array of structures
    s = new student[n];

    // data reading
    ifstream file("/Users/ilagoncarenko/Downloads/Практики /Лаба 1 версия 3.0(тест на исправление)/Лаба 1 версия 3.0(тест на исправление)/student.txt", ios::binary);
    if (!file) {
        cout << "Error opening student.txt file\n";
        return;
    }
    file.read((char*)s, sizeof(student) * n);
    file.close();

    // displaying student data
    for (int i = 0; i < n; i++){
        cout << "___________________________________" << endl;
        cout << "\nData №" << i + 1 << ':' << endl;
        cout << "Full name: " << s[i].surname << ' ' << s[i].name << ' ' << s[i].patronymic << endl;
        cout << "Group: " << s[i].group << endl;
        cout << "___________________________________" << endl;
    }
}

void ReadDataTeachers(teachers* &t,int &n)
{
    // read number of records
    ifstream filenumber("/Users/ilagoncarenko/Downloads/Практики /Лаба 1 версия 3.0(тест на исправление)/Лаба 1 версия 3.0(тест на исправление)/NumberTeachers.txt", ios::binary);
    if (!filenumber) {
        cout << "Error opening NumberTeachers.txt file\n";
        return;
    }
    filenumber >> n;
    filenumber.close();

    // memory allocation for an array of structures
    t = new teachers[n];

    // data reading
    ifstream file("/Users/ilagoncarenko/Downloads/Практики /Лаба 1 версия 3.0(тест на исправление)/Лаба 1 версия 3.0(тест на исправление)/teachers.txt", ios::binary);
    if (!file) {
        cout << "Error opening teachers.txt file\n";
        return;
    }
    file.read((char*)t, sizeof(teachers) * n);
    file.close();

    // displaying student data
    for (int i = 0; i < n; i++){
        cout << "___________________________________" << endl;
        cout << "\nData №" << i + 1 << ':' << endl;
        cout << "Full name: " << t[i].surname << ' ' << t[i].name << ' ' << t[i].patronymic << endl;
        cout << "Cabinet: " << t[i].cabinet << endl;
        cout << "___________________________________" << endl;
    }
}

