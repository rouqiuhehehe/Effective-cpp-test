//
// Created by admin on 2023/1/30.
//
#include "log.h"
class A
{
    virtual void a ()
    {
        myDebug << "a" << std::endl;
    }
};

class B : public A
{
    virtual void b ()
    {
        myDebug << "b" << std::endl;
    }
};
class C
{
    virtual void f () {}
};
class D : public C
{

};
void testTypeInfo ()
{
    B b;
    // 第一个虚函数的指针
    auto *vptr = (uintptr_t *)*(uintptr_t *)(&b);
    myDebug << ((std::type_info *)*(vptr - 1))->name() << std::endl;

    ((void (*) ())(*(vptr)))();
    ((void (*) ())(*(vptr + 1)))();

    C *d = new D;
    myDebug << typeid(*d).name();
}