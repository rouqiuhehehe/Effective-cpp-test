//
// Created by ASUS on 2023/1/24.
//

#ifndef TEST_CPP_LIB_LOG_H_
#define TEST_CPP_LIB_LOG_H_

#include <iostream>
#ifdef NDEBUG
#define myDebug 0 && std::cout
#define myWarning 0 && std::cout
#else
#define myDebug std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << "\t"
#define myWarning std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << "\twarning: "
#endif
#endif //TEST_CPP_LIB_LOG_H_
