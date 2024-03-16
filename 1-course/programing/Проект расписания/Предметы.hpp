//
//  Предметы.hpp
//  Проект расписания
//
//  Created by Илья Гончаренко on 18.06.2023.
//

#ifndef _________hpp
#define _________hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#endif /* _________hpp */
//реализация класса предмет какой хранит название предмета
static int token = 0;
class Item
{
protected:
    string m_nameItem;
    int m_token;
public:
    Item(string name = "Название не указано"):m_nameItem(name),m_token(token+=1) {}
    void changeNameItem(string name);
    string getname()const;
    int getToken()const;
};



class Itemdata : public Item
{
private:
    int m_yearlyScore;
    int m_numberOfPairs;
    int m_modules;
public:
    
    Itemdata()
    {}
    Itemdata(string name,int yearlyScore = 0, int numberOfPairs = 0, int modules = 0)
    :Item(name),m_yearlyScore(yearlyScore),m_numberOfPairs(numberOfPairs),m_modules(modules)
    {}
    
    void info();
    
    void changedata(int yearlyScore = 0, int numberOfPairs = 0, int modules = 0);
    
    friend istream& operator>> (istream &in, Itemdata &itemdata);
    friend ostream& operator<< (ostream &out, const Itemdata itemdata);
};



struct Node{
    Itemdata m_itemdata;
    Node* m_prev;
    Node* m_next;
    Node(Itemdata itemdata,Node *prev = nullptr, Node* next = nullptr)
    :m_itemdata(itemdata),m_prev(prev),m_next(next)
    {}
};

class DoubleLinkedList
{
private:
    
    Node* m_first;
    Node* m_last;
public:
    DoubleLinkedList():m_first(nullptr),m_last(nullptr)
    {}
    
    bool is_empty();

    void push_back(Itemdata itemdata); 
    void print(); 
    Node* find(int token);
};
