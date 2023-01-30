//
// Created by admin on 2023/1/12.
//

#ifndef CPP_TEST__POINTWATHER_H_
#define CPP_TEST__POINTWATHER_H_

#include <cstdio>
#include <set>
class PointWatcher
{
public:
    inline void *operator new (size_t s)
    {
        void *p = ::operator new(s);
        pointSet.insert(static_cast<PointWatcher *>(p));

        return p;
    }
    inline void operator delete (void *p)
    {
        ::operator delete(p);
        pointSet.erase(static_cast<PointWatcher *>(p));
    }

    static inline bool checkPointIsUsed (PointWatcher *p)
    {
        return pointSet.find(p) != pointSet.end();
    }

private:
    static std::set <PointWatcher *> pointSet;
};

std::set <PointWatcher *> PointWatcher::pointSet = std::set <PointWatcher *>();
#endif //CPP_TEST__POINTWATHER_H_
