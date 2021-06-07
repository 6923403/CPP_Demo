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
        LOG(ERROR) << "数据库连接失败";
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

        char sql_str[512] = {'\0'};
        snprintf(sql_str, sizeof(sql_str), "%s('%s','%s','%s');", "INSERT INTO user (username, password, registration_time) VALUES", username.c_str(), password.c_str(), re_time);
        int flag = mysql_real_query(mysql, sql_str, sizeof(sql_str));
        if(flag)
        {
            return false;
        }

        return true;
    }
}

bool Connect_Sql::delete_data(std::string data) {
    char sql_str[512] = {'\0'};
    snprintf(sql_str, sizeof(sql_str), "%s'%s';", "DELETE FROM user WHERE username = ", data.c_str());
    //std::cout << sql_str << std::endl;
    int flag = mysql_real_query(mysql, sql_str, sizeof(sql_str));

    if(flag)
    {
       return false;
    }

    return true;
}

bool Connect_Sql::show_information(MYSQL_RES *res, MYSQL *mysql)
{
    MYSQL_ROW row;
    MYSQL_FIELD *fields;
    unsigned long *un_sqllen;
    unsigned un_sqlnum = -1;

    row = mysql_fetch_row(res);

    //unsigned int mysql_num_fields(MYSQL_RES *result) 数据长度
    un_sqlnum = mysql_num_fields(res);
    if(un_sqlnum == -1)
        return false;
    //std::cout << "sql_num = "d d << un_sqlnum << std::endl;

    //unsigned long * mysql_fetch_lengths(MYSQL_RES *result) 列长
    un_sqllen = mysql_fetch_lengths(res);

    fields = mysql_fetch_fields(res);

    if(row) {
        for (int i = 0; i < un_sqlnum; i++)
        {
            std::cout << fields[i].name << std::endl;
        }

        return true;
    }
    else
        return false;
}

bool Connect_Sql::search_data()
{
    char str_sql[512] = "SELECT * FROM user;";
    if(mysql_real_query(mysql, str_sql, sizeof(str_sql)))
    {
        return false;
    }

    MYSQL_RES* res;
    int status = mysql_store_result_nonblocking(mysql, &res);
    if(status != 0)
    {
        std::string st;
        switch (status) {
            case '1':
                st = "NET_ASYNC_NOT_READY";
                break;
            case 2:
                st = "NET_ASYNC_ERROR";
                break;
            case '3':
                st = "NET_ASYNC_COMPLETE_NO_MORE_RESULTS";
                LOG(INFO) << st;
        }
        return false;
    }

    if(show_information(res, mysql))
    {
        return true;
    }
    else
    {
        return false;
    }
}