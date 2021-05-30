#ifndef MYSQL_CONNECT_SQL_H
#define MYSQL_CONNECT_SQL_H

#include <iostream>
#include <string>
#include <mysql/mysql.h>

class Connect_Sql
{
public:
    Connect_Sql();
    ~Connect_Sql();

    bool connect_mysql(std::string addr, std::string username, std::string password, int port);

private:
    MYSQL* mysql;
};

#endif //MYSQL_CONNECT_SQL_H
