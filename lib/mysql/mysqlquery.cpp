//
// Created by Administrator on 2023/2/4.
//

#include "mysqlquery.h"
#include "mysqlresult.h"
/*
 * MysqlQuery::MysqlQueryPrivate
 * */
class MysqlQuery::MysqlQueryPrivate
{
public:
    explicit MysqlQueryPrivate (MysqlResult *result);
    ~MysqlQueryPrivate () noexcept;

    MysqlResult *result;
    MysqlDatabase db;
};
MysqlQuery::MysqlQueryPrivate::MysqlQueryPrivate (MysqlResult *result)
    : result(result)
{
}
MysqlQuery::MysqlQueryPrivate::~MysqlQueryPrivate () noexcept
{
    delete result;
}

/*
 * MysqlQuery
 * */
MysqlQuery::~MysqlQuery () noexcept
{
    delete d;
}
MysqlQuery::MysqlQuery (const std::string &query)
    : d(new MysqlQueryPrivate(new MysqlResult))
{
    d->db = MysqlDatabase::database();
    exec(query);
}
MysqlQuery::MysqlQuery (const std::string &query, const MysqlDatabase &db)
    : d(new MysqlQueryPrivate(new MysqlResult))
{
    d->db = db;
    exec(query);
}
MysqlQuery::MysqlQuery (const MysqlDatabase &db)
    : d(new MysqlQueryPrivate(new MysqlResult))
{
    d->db = db;
}
bool MysqlQuery::exec (const std::string &query)
{
    return false;
}
