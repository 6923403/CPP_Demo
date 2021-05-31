#ifndef CONNECT_SQL_H
#define CONNECT_SQL_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <map>
#include <mysql/mysql.h>

class Connect_Sql
{
public:
    Connect_Sql();
    ~Connect_Sql();

    bool connect_mysql(std::string addr, std::string db_name, std::string username, std::string password, int port);
    bool insert_data(std::map<std::string, std::string> m_user);

private:
    MYSQL* mysql;
};

#endif //CONNECT_SQL_H
