//
//  Предметы.cpp
//  Проект расписания
//
//  Created by Илья Гончаренко on 18.06.2023.
//

#include "Предметы.hpp"

void Item::changeNameItem(string name){m_nameItem=name;}

string Item::getname()const{return m_nameItem;}

int Item::getToken()const{return m_token;}




void Itemdata::info()
{
    cout<<"Название предмета : "<<getname()<<'\n';
    cout<<"Оценка за год : "<<m_yearlyScore<<'\n';
    cout<<"Количество выделеных академ. часов : "<<m_numberOfPairs<<'\n';
    cout<<"Количество модулей : "<<m_modules<<'\n';
}

void Itemdata::changedata(int yearlyScore, int numberOfPairs, int modules)
{
    
    if(yearlyScore != 0)     {m_yearlyScore = yearlyScore;}
    
    if(numberOfPairs != 0)   {m_numberOfPairs = numberOfPairs;}
    
    if(modules !=0)          { m_modules = modules;}
}

istream& operator>> (istream &in, Itemdata &itemdata)
{
    in>>itemdata.m_nameItem;
    in>>itemdata.m_yearlyScore;
    in>>itemdata.m_numberOfPairs;
    in>>itemdata.m_modules;
    return in;
}

ostream& operator<< (ostream &out, const Itemdata itemdata)
{
    out<<"////////////////////////////////////"<<'\n';
    out<<"Номер предмета для поиска/взаимодействия : "<<itemdata.m_token<<'\n';
    out<<"Название предмета : "<<itemdata.m_nameItem<<'\n';
    out<<"Оценка за год : "<<itemdata.m_yearlyScore<<'\n';
    out<<"Количество пар данного предмета : "<<itemdata.m_numberOfPairs<<'\n';
    out<<"Количество модулей : "<<itemdata.m_modules<<'\n';
    //out<<"////////////////////////////////////"<<'\n';
        return out;
    
}
