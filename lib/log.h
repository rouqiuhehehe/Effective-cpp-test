//
// Created by ASUS on 2023/1/24.
//

#ifndef TEST_CPP_LIB_LOG_H_
#define TEST_CPP_LIB_LOG_H_

#include <iostream>
#ifdef NDEBUG
#define debug 0 && std::cout
#else
#define debug std::cout
#endif
#endif //TEST_CPP_LIB_LOG_H_
