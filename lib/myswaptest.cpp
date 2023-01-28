//
// Created by ASUS on 2023/1/17.
//

#include "myswaptest.h"
#include <string>
#include <iostream>

class MySwapTest::MyPimpl
{
public:
    explicit MyPimpl (std::string str) : c(std::move(str))
    {
    }

    [[nodiscard]] const std::string &getC () const
    {
        return c;
    }
private:
    std::string c;
};
void swap (MySwapTest &lhs, MySwapTest &rhs);
MySwapTest::MySwapTest () : pimpl(new MyPimpl("dsc"))
{
}
MySwapTest::MySwapTest (const MySwapTest &rhs)
{
    std::cout << "调用复制构造函数" << std::endl;
    pimpl = new MyPimpl(rhs.pimpl->getC());
}
MySwapTest &MySwapTest::operator= (const MySwapTest &rhs)
{
    if (this == &rhs)
        return *this;

    new(this) MySwapTest(rhs);
    return *this;
}
MySwapTest::~MySwapTest ()
{
    std::cout << "调用析构函数" << std::endl;
    delete pimpl;
}
MySwapTest::MySwapTest (MySwapTest &&rhs) noexcept
{
    std::cout << "调用移动复制构造函数" << std::endl;
    new(this) MySwapTest((const MySwapTest &)rhs);
}
MySwapTest &MySwapTest::operator= (MySwapTest &&rhs) noexcept
{
    std::cout << "调用移动赋值构造函数" << std::endl;
    if (this == &rhs)
        return *this;
    new(this) MySwapTest(rhs);
    return *this;
}