//
//  main.cpp
//  Проект расписания
//
//  Created by Илья Гончаренко on 18.06.2023.
//


#include "Предметы.hpp"
//Можно использовать для функции ввода нового предмета(понятное дело переработав под нужды кода)
//string input;
//while (getline(cin, input) && !input.empty()) {
//    istringstream iss(input);
//    WeatherData data;
//    string token;
//
//    getline(iss, token, ',');
//    data.stationId = stoi(token);
//
//    getline(iss, data.location, ',');
//
//    getline(iss, data.date, ',');
//
//    getline(iss, token, ',');
//    data.hour = stoi(token);
//
//    getline(iss, token);
//    data.temperature = stoi(token);
//
//    weatherData.push_back(data);
//}

int main() {
    string input;
    DoubleLinkedList p;
    cout<<"f"<<'\n';    while(getline(cin,input)&&!input.empty()){
        istringstream iss(input);
       
        
        stringstream ss(input); // Создаем поток из строки
        string nameItem;
        int yearlyScore;
        int numberOfPairs;
        int modules;
        
        // Извлекаем значения из потока
        ss >> nameItem>>yearlyScore>>numberOfPairs>>modules;
        
        // Создаем объект класса MyClass, передавая извлеченные параметры
        Itemdata item(nameItem,yearlyScore,numberOfPairs,modules);
        p.push_back(item);
        // Продолжаем работу с объектом MyClass..
        
       
    }
    p.print();
    int token =3;
    Node* found = p.find(token);
    cout<<found->m_itemdata;
    
//    class Itemdata itemdata;
//
//    cin>>itemdata;
//    cout<<itemdata;
    return 0;
}
