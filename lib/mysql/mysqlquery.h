//
// Created by Administrator on 2023/2/4.
//

#ifndef TEST_CPP_LIB_MYSQL_MYSQLQUERY_H_
#define TEST_CPP_LIB_MYSQL_MYSQLQUERY_H_

#include <string>
#include "mysqldatabase.h"
class MysqlResult;
class MysqlQuery
{
    friend class MysqlDatabase;
public:
    explicit MysqlQuery (const std::string &query);
    MysqlQuery (const std::string &query, const MysqlDatabase &db);
    explicit MysqlQuery (const MysqlDatabase &db);
    ~MysqlQuery() noexcept;

    bool exec(const std::string& query);

private:
    class MysqlQueryPrivate;
    MysqlQueryPrivate *d;
};
#endif //TEST_CPP_LIB_MYSQL_MYSQLQUERY_H_
