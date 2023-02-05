//
// Created by Administrator on 2023/2/4.
//

#ifndef TEST_CPP_LIB_MYSQL_MYSQLERROR_H_
#define TEST_CPP_LIB_MYSQL_MYSQLERROR_H_
#include <string>
#include <exception>
class MysqlError final : public std::exception
{
public:
    [[nodiscard]] const char *what () const noexcept final;
    void setError(std::string error);
private:
    std::string errorString;
};

#endif //TEST_CPP_LIB_MYSQL_MYSQLERROR_H_
