//
// Created by ASUS on 2023/1/12.
//
#include <mysql.h>
#include "log.h"
#include <string>
extern void testXORLinkedList ();
extern void testTypeInfo ();
int main ()
{
    auto *sql = new MYSQL;
    mysql_init(sql);
    if (!mysql_real_connect(
        sql,
        "localhost",
        "root",
        "jianv4as",
        "no26_detective_hal",
        0,
        nullptr,
        0
    ))
        debug << "连接失败：" << mysql_error(sql) << std::endl;
    else
        debug << "连接成功！" << std::endl;

    std::string query = "select * from opera_list";
    if (mysql_real_query(sql, query.c_str(), query.size()))
        debug << "查询失败：" << mysql_error(sql) << std::endl;

    auto *res = mysql_store_result(sql);
    if (!res)
        debug << "返回值错误" << std::endl;

    unsigned int fieldsCount = mysql_num_fields(res);
    for (int i = 0; i < fieldsCount; ++i)
    {
        MYSQL_FIELD *field = mysql_fetch_field_direct(res, i);
        std::cout << field->name << "\t";
    }
    std::cout << std::endl;

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)))
    {
        debug << mysql_num_fields(res) << std::endl;
        for (int i = 0; i < fieldsCount; ++i)
        {
            char *v = row[i];
            if (v == nullptr)
                std::cout << "null" << "\t";
            else
                std::cout << row[i] << "\t";
        }
        std::cout << std::endl;
    }

    mysql_free_result(res);
    mysql_close(sql);
    delete sql;
    // testXORLinkedList();
    // testTypeInfo();
    return 0;
}