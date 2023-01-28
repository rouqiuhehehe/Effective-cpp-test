//
// Created by ASUS on 2023/1/17.
//

#ifndef TEST_CPP__MYSWAPTEST_H_
#define TEST_CPP__MYSWAPTEST_H_

#include <algorithm>
class MySwapTest
{
public:
    MySwapTest ();
    MySwapTest (const MySwapTest &);
    MySwapTest (MySwapTest &&) noexcept;
    MySwapTest &operator= (const MySwapTest &);
    MySwapTest &operator= (MySwapTest &&) noexcept;
    ~MySwapTest ();

    friend void swap (MySwapTest &, MySwapTest &);
private:
    class MyPimpl;
    MyPimpl *pimpl = nullptr;
};

inline void swap (MySwapTest &lhs, MySwapTest &rhs)
{
    using std::swap;

    swap(lhs.pimpl, rhs.pimpl);
}
#endif //TEST_CPP__MYSWAPTEST_H_
