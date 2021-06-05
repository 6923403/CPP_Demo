#ifndef CONNECT_SQL_H
#define CONNECT_SQL_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <mysql/mysql.h>

#include "../log/easylogging.h"

class Connect_Sql
{
public:
    Connect_Sql();
    ~Connect_Sql();

    bool connect_mysql(std::string addr, std::string db_name, std::string username, std::string password, int port);
    bool insert_data(std::map<std::string, std::string> m_user);

    bool delete_data(std::string data);
    bool delete_data(std::string type, std::string data);

    bool search_data();
    bool search_data(std::string data);

    bool show_information(MYSQL_RES* res, MYSQL* mysql);

private:
    MYSQL* mysql;
};

#endif //CONNECT_SQL_H
