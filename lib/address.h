//
// Created by ASUS on 2023/1/23.
//

#ifndef TEST_CPP_LIB_ADDRESS_H_
#define TEST_CPP_LIB_ADDRESS_H_

#if __cplusplus >= 201703
template<class T>
inline T *addressOf (T &rhs) noexcept
{
    if constexpr(std::is_pointer<T>::value)
        return rhs;

    return reinterpret_cast<T *>(&const_cast<char &>(reinterpret_cast<const volatile char &> (rhs)));
}
#elif __cplusplus >= 201103
template<class T, std::enable_if<std::is_pointer<T>::value, T> * = nullptr>
inline T *addressOf (T &rhs) noexcept
{
    return rhs;
}
template<class T, std::enable_if<!std::is_pointer<T>::value, T> * = nullptr>
inline T *addressOf (T &rhs) noexcept
{
    return reinterpret_cast<T *>(&const_cast<char &>(reinterpret_cast<const volatile char &> (rhs)));
}
#endif

#endif //TEST_CPP_LIB_ADDRESS_H_
