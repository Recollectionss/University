//
//  DoubleLinkedList.cpp
//  Проект расписания
//
//  Created by Илья Гончаренко on 03.07.2023.
//

#include <stdio.h>
#include "Предметы.hpp"
bool DoubleLinkedList::is_empty() {return m_first == nullptr;}

void DoubleLinkedList::push_back(Itemdata itemdata)
{
        Node* p = new Node(itemdata);
    
        if (is_empty())
        {
            m_first = p;
            m_last = p;
            return;
        }
        m_last->m_next = p;
        m_last = p;
    }


void DoubleLinkedList::print()
{
        if (is_empty()) return;
    
        Node* p = m_first;
    
        while (p)
        {
            cout << p->m_itemdata << " ";
            p = p->m_next;
        }
        cout << endl;
    }

Node* DoubleLinkedList::find(int token)
{
    Node* findFirst=m_first;
    Node* findLast = m_last;
    
    while(findFirst&& findFirst->m_itemdata.getToken()!=token&& findLast->m_itemdata.getToken() != token)
    {
        findFirst=findFirst->m_next;
        findLast=findLast->m_prev;
    }
    if(findFirst->m_itemdata.getToken()==token)
        {return findFirst?findFirst:nullptr;}
    else
        {return findLast?findLast:nullptr;}
}
