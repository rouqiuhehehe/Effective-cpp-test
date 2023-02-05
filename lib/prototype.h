//
// Created by Administrator on 2023/2/4.
//

#ifndef TEST_CPP_LIB_PROTOTYPE_H_
#define TEST_CPP_LIB_PROTOTYPE_H_

class Prototype
{
public:
    Prototype () = default;
    virtual ~Prototype () = default;

    virtual Prototype clone () const = 0;
protected:
    Prototype (const Prototype &) = default;
    Prototype &operator= (const Prototype &) = default;

#if __cplusplus >= 201103
    Prototype (Prototype &&) noexcept = default;
    Prototype &operator= (Prototype &&) noexcept = default;
#endif
};
#endif //TEST_CPP_LIB_PROTOTYPE_H_
