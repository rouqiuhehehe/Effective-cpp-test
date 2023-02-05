//
// Created by Administrator on 2023/2/1.
//

#include "mysqldatabase.h"
#include "log.h"
#include <utility>
#include <mysql.h>
#include "mysqlquery.h"

#define BEGIN_TRAN "START TRANSACTION"
#define SET_UNAUTO "SET AUTOCOMMIT=0"
#define SET_AUTO "SET AUTOCOMMIT=1"
#define COMMIT_TRAN "COMMIT"
#define ROLLBACK_TRAN "ROLLBACK"
using std::string;

/*
 * MysqlDatabase::MysqlDatabasePrivate
 * */
const char *MysqlDatabase::defaultConnectionName = "default_connection_name";
std::map <std::string, MysqlDatabase> MysqlDatabase::databaseMap;

class MysqlDatabase::MysqlDatabasePrivate
{
public:
    explicit MysqlDatabasePrivate (string name)
        : databaseName(std::move(name)), db() {}

    inline bool open ();
    inline void close ();

    string connectName;
    string databaseName;
    MYSQL db {};
    string username;
    string password;
    string hostname;
    int port = 0;
    bool isOpen = false;
    bool isOpenError = false;
    MysqlError error;
};
bool MysqlDatabase::MysqlDatabasePrivate::open ()
{
    if (!mysql_real_connect(
        &db,
        hostname.c_str(),
        username.c_str(),
        password.c_str(),
        databaseName.c_str(),
        port,
        nullptr,
        0
    ))
    {
        error.setError(mysql_error(&db));
        isOpenError = true;
        return false;
    }
    isOpen = true;
    isOpenError = false;
    return true;
}
void MysqlDatabase::MysqlDatabasePrivate::close ()
{
    isOpen = false;
    mysql_close(&db);
}

/*
 * MysqlDatabase
 * */
MysqlDatabase::~MysqlDatabase () noexcept
{
    removeDatabase(d->connectName);
    delete d;
}
const string &MysqlDatabase::name () const
{
    return d->connectName;
}
MysqlDatabase MysqlDatabase::addDatabase (const string &name)
{
    MysqlDatabase db(name);

    if (databaseMap.count(name))
    {
        myWarning << "数据库名称已经存在，将替换原先数据库" << std::endl;
        databaseMap[name] = db;
    }
    else
        databaseMap.insert(MapPair(name, db));

    return db;
}
MysqlDatabase::MysqlDatabase (const string &name)
    : d(new MysqlDatabasePrivate(name))
{
    if (databaseMap.count(d->connectName))
    {
        myWarning << "数据库名称已经存在，将替换原先数据库" << std::endl;
        databaseMap[d->connectName] = *this;
    }
    else
        databaseMap.insert(MapPair(d->connectName, *this));
}
MysqlDatabase MysqlDatabase::database (const string &name)
{
    return databaseMap[name];
}
void MysqlDatabase::removeDatabase (const string &name)
{
    databaseMap.erase(name);
}
void MysqlDatabase::setDatabaseName (const string &name)
{
#if __cplusplus > 201402L
    auto v = databaseMap.extract(d->connectName);
    v.key() = name;
    databaseMap.insert(std::move(v));
#else
    databaseMap.erase(name);
    databaseMap.insert(MapPair(name, *this));
#endif

    d->connectName = name;
}
void MysqlDatabase::setUserName (const string &name)
{
    d->username = name;
}
void MysqlDatabase::setPassword (const string &password)
{
    d->password = password;
}
void MysqlDatabase::setHostName (const string &host)
{
    d->hostname = host;
}
void MysqlDatabase::setPort (int p)
{
    d->port = p;
}
std::string MysqlDatabase::userName () const
{
    return d->username;
}
std::string MysqlDatabase::password () const
{
    return d->password;
}
std::string MysqlDatabase::hostName () const
{
    return d->hostname;
}
int MysqlDatabase::port () const
{
    return d->port;
}
bool MysqlDatabase::open (const string &user, const string &password)
{
    d->username = user;
    d->password = password;
    return open();
}
bool MysqlDatabase::open ()
{
    return d->open();
}
MysqlQuery MysqlDatabase::exec (const std::string &sql) const
{
    return { sql, *this };
}
MysqlError MysqlDatabase::lastError () const
{
    return d->error;
}
void MysqlDatabase::close ()
{
    d->close();
}
bool MysqlDatabase::isOpen () const
{
    return d->isOpen;
}
bool MysqlDatabase::isOpenError () const
{
    return d->isOpenError;
}
bool MysqlDatabase::transaction ()
{
    int res = mysql_query(&d->db, BEGIN_TRAN);
    if (!checkRes(res, 0))
        return false;
    res = mysql_query(&d->db, SET_UNAUTO);
    if (!checkRes(res, 0))
        return false;

    return true;
}
bool MysqlDatabase::commit ()
{
    int res = mysql_query(&d->db, COMMIT_TRAN);
    if (!checkRes(res, 0))
        return false;
    res = mysql_query(&d->db, SET_AUTO);
    if (!checkRes(res, 0))
        return false;

    return true;
}
bool MysqlDatabase::rollback ()
{
    int res = mysql_query(&d->db, ROLLBACK_TRAN);
    if (!checkRes(res, 0))
        return false;
    res = mysql_query(&d->db, SET_AUTO);
    if (!checkRes(res, 0))
        return false;

    return true;
}
bool MysqlDatabase::checkRes (int res, int code) const
{
    if (res != code)
    {
        d->error.setError(mysql_error(&d->db));
        return false;
    }

    return true;
}