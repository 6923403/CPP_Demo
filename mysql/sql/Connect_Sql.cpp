#include "Connect_Sql.h"

Connect_Sql::Connect_Sql() : mysql(nullptr)
{
}

Connect_Sql::~Connect_Sql()
{
}

bool Connect_Sql::connect_mysql(std::string addr, std::string username, std::string password, int port)
{
    while(!mysql)
    {
        mysql = mysql_init(mysql);
    }

    mysql = mysql_real_connect(mysql, addr.c_str(), username.c_str(), password.c_str(), "servert", port, NULL, 0);

    if(!mysql)
    {
        //LOG("未连接成功")
        return false;
    }

    return true;
}