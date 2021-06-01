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
    if(mysql == nullptr)
    {
        return false;
    }

    mysql = mysql_real_connect(mysql, addr.c_str(), username.c_str(), password.c_str(), db_name.c_str(), 0, NULL, 0);

    if(mysql == nullptr)
    {
        //LOG("未连接成功")
        return false;
    }

//    if(mysql_set_character_set(mysql, "utf8"))
//    {
//        return false;
//    }

    return true;
}

bool Connect_Sql::insert_data(std::map<std::string, std::string> m_user)
{
    using namespace std::chrono;

    std::map<std::string, std::string>::iterator it;
    it = m_user.begin();
    for(it; it != m_user.end(); it++)
    {
        std::string username(it->first), password(it->second);

        std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); //当前时间
        char re_time[256] = {0};
        std::strftime(re_time, sizeof(re_time), "%Y-%m-%d %X", std::localtime(&now));

        char sql_str[512];
        snprintf(sql_str, sizeof(sql_str), "%s('%s','%s','%s');", "INSERT INTO user (username, password, registration_time) VALUES", username.c_str(), password.c_str(), re_time);
        int flag = mysql_real_query(mysql, sql_str, sizeof(sql_str));
        if(flag)
        {
            return false;
        }

        return true;

    }
}
