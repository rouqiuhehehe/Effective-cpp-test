//
// Created by admin on 2023/1/30.
//
#include "myxorlinkedlist.h"
#include "log.h"
void testXORLinkedList() {
    MyXORLinkedList <int> a;
    MyXORLinkedList <int> b;
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    a.push(5);
    a.push(6);
    a.push(7);
    a.erase(2);
    // a.traverseReverse(
    //     [] (const int &v)
    //     {
    //         myDebug << v << std::endl;
    //     }
    // );
    // for (auto &v : a)
    // {
    //     myDebug << v << std::endl;
    // }

    for (MyXORLinkedList <int>::IteratorReverse i = a.rbegin(); i != a.rend(); ++i)
    {
        myDebug << *i << std::endl;
    }
    swap(a, b);
}