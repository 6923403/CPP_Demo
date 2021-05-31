#include "Connect_Sql.h"

Connect_Sql::Connect_Sql() : mysql(NULL)
{
}

Connect_Sql::~Connect_Sql()
{
    mysql_close(mysql);
}

bool Connect_Sql::connect_mysql(std::string addr, std::string db_name, std::string username, std::string password, int port)
{
    mysql = mysql_init(mysql);
    if(!mysql)
    {
        return false;
    }

    mysql = mysql_real_connect(mysql, addr.c_str(), username.c_str(), password.c_str(), db_name.c_str(), port, NULL, 0);

    if(!mysql)
    {
        //LOG("未连接成功")
        return false;
    }

    if(mysql_set_character_set(mysql, "utf8"))
    {
        return false;
    }

    return true;
}

bool Connect_Sql::insert_data(std::map<std::string, std::string> m_user)
{
}