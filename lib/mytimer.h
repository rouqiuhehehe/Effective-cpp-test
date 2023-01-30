//
// Created by admin on 2023/1/12.
//

#ifndef CPP_TEST__MYTIMER_H_
#define CPP_TEST__MYTIMER_H_
#include <windows.h>
#include <functional>
#include <map>

#ifndef NDEBUG
#include <iostream>
#endif
class MyTimer
{
public:
    typedef std::function <void ()> CallBack;

    MyTimer ();
    explicit MyTimer (size_t);
    ~MyTimer ()
    {
        killTimer();
    }

    void startTimer (CallBack &&fun);
    void startTimer (size_t t, CallBack &&fun)
    {
        time = t;
        startTimer(std::move(fun));
    }
    void killTimer () const
    {
        if (callbackMap.find(id) != callbackMap.end())
        {
            callbackMap.erase(id);
            KillTimer(nullptr, id);
        }
    }

    static void closeMessage ()
    {
        needMessage = false;
    }
    // 工作线程默认没有消息队列，请手动开启消息队列
    static void createMessage ();
private:
    typedef std::map <size_t, CallBack *> CallBackMap;

    size_t time = 0;
    size_t id = 0;
    static CallBackMap callbackMap;
    static volatile bool needMessage;

    CallBack callback;

    static void timeOutCallback (HWND, UINT, UINT_PTR, DWORD);
};
#endif //CPP_TEST__MYTIMER_H_
