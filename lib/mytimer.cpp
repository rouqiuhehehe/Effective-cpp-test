//
// Created by admin on 2023/1/12.
//

#include "mytimer.h"

volatile bool MyTimer::needMessage = false;
MyTimer::CallBackMap MyTimer::callbackMap = MyTimer::CallBackMap();

MyTimer::MyTimer ()
{
    new(this) MyTimer(0);
}
MyTimer::MyTimer (size_t t)
    : time(t)
{
}
void MyTimer::startTimer (MyTimer::CallBack &&fun)
{
    callback = std::move(fun);

    id = SetTimer(nullptr, 1, time, MyTimer::timeOutCallback);
    callbackMap.insert(std::pair <size_t, CallBack *>(id, &callback));
}
void MyTimer::timeOutCallback (HWND, UINT c, UINT_PTR id, DWORD)
{
    // std::cout << id << std::endl << c << std::endl;

    auto callback = callbackMap.find(id);
    if (callback != callbackMap.end())
        (*callback->second)();
}
void MyTimer::createMessage ()
{
#ifndef NDEBUG
    std::cout << "开启消息队列" << std::endl;
#endif
    needMessage = true;
    MSG msg;
    while (!callbackMap.empty() && needMessage)
    {
#ifndef NDEBUG
        std::cout <<
#endif
        GetMessage(&msg, nullptr, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}