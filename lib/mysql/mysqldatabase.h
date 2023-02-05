//
// Created by Administrator on 2023/2/1.
//

#ifndef TEST_CPP_LIB_MYSQL_MYSQLDATABASE_H_
#define TEST_CPP_LIB_MYSQL_MYSQLDATABASE_H_

#include <map>
#include "mysqlerror.h"
class MysqlQuery;
class MysqlDatabase
{
public:
    explicit MysqlDatabase (const std::string &name = defaultConnectionName);
    ~MysqlDatabase () noexcept;

    static MysqlDatabase addDatabase (const std::string &name = defaultConnectionName);
    static MysqlDatabase database (const std::string &name = defaultConnectionName);
    static void removeDatabase (const std::string &name);

    bool open ();
    bool open (const std::string &user, const std::string &password);
    void close ();
    [[nodiscard]] bool isOpen () const;
    [[nodiscard]] bool isOpenError () const;
    [[nodiscard]] MysqlQuery exec (const std::string &sql) const;
    [[nodiscard]] MysqlError lastError () const;

    bool transaction ();
    bool commit ();
    bool rollback ();

    [[nodiscard]] inline const std::string &name () const;
    inline void setDatabaseName (const std::string &name);
    inline void setUserName (const std::string &name);
    inline void setPassword (const std::string &password);
    inline void setHostName (const std::string &host);
    inline void setPort (int p);
    [[nodiscard]] inline std::string userName () const;
    [[nodiscard]] inline std::string password () const;
    [[nodiscard]] inline std::string hostName () const;
    [[nodiscard]] inline int port () const;
private:
    typedef std::pair <std::string, MysqlDatabase> MapPair;
    static const char *defaultConnectionName;
    static std::map <std::string, MysqlDatabase> databaseMap;

    [[nodiscard]] inline bool checkRes (int, int) const;

private:
    class MysqlDatabasePrivate;
    MysqlDatabasePrivate *d;
};
#endif //TEST_CPP_LIB_MYSQL_MYSQLDATABASE_H_
