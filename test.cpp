//
// Created by ASUS on 2023/1/12.
//
#include "myxorlinkedlist.h"
#include <list>
#include "log.h"
int main ()
{
    std::cout << __cplusplus << std::endl;
    std::list<int *> *c = new std::list<int *>;
    MyXORLinkedList<int> a;
    MyXORLinkedList<int> b;
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    a.push(5);
    a.push(6);
    a.push(7);
    a.erase(2);
    a.traverse([] (const int &v)
    {
      debug << v << std::endl;
    });
    swap(a, b);
    return 0;
}