//
// Created by Administrator on 2023/2/4.
//

#include "mysqlerror.h"
/*
 * MysqlDatabaseError
 * */
const char *MysqlError::what () const noexcept
{
    return errorString.c_str();
}
void MysqlError::setError (std::string error)
{
    errorString = std::move(error);
}