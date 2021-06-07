#include <iostream>
#include <getopt.h>

#include "sql/Connect_Sql.h"
INITIALIZE_EASYLOGGINGPP //log需要

void usage()
{
      std::cout << "./mysql -a localhost -d sqlname -u root -p password -t 3306 \n"
                << "-a: sqladdr \n"
                << "-d: database_name \n"
                << "-u: username \n"
                << "-p: password \n"
                << "-t: sql port \n"
                << "-h: help menu"
                << std::endl;
}

static struct option longOpts[] = {
        {"ip_addr", required_argument, NULL, 'a'},
        {"database", required_argument, NULL, 'd'},
        {"username", required_argument, NULL, 'u'},
        {"password", required_argument, NULL, 'p'},
        {"port", required_argument, NULL, 't'},
        {"help", required_argument, NULL, 'h'},
        {0, 0,0, 0}
};

int main(int argc, char** argv)
{
    std::string db_name = "servert";
    std::string username = "root";
    std::string password = "";
    std::string ip_addr = "localhost";
    int port = 3306;

    int opt = 0;
    int optionIndex = 0;
    while((opt = getopt_long(argc, argv, "adup:th", longOpts, &optionIndex)) != -1)
    {
        switch (opt) {
            case 'a':
                ip_addr = optarg;
                break;
            case 'd':
                db_name = optarg;
                break;
            case 'u':
                username = optarg;
                break;
            case 'p':
                password = optarg;
                break;
            case 't':
                port = atoi(optarg);
                break;
            case 'h':
                usage();
                exit(0);
            default:
                break;
        }
    }


//    LOG(TRACE)   << "***** trace log  *****";
//    LOG(DEBUG)   << "***** debug log  *****";
//    LOG(ERROR)   << "***** error log  *****";
//    LOG(WARNING) << "***** warning log  *****";
//    LOG(INFO)    << "***** info log  *****";

    Connect_Sql sql;
    if(sql.connect_mysql(ip_addr, db_name, username, password, port))
    {
        LOG(INFO) << "连接数据库成功";
    }
    else
    {
        LOG(ERROR) << "连接数据库失败";
    }

    std::map<std::string, std::string> m_user;
    std::string n, q;
    std::cout << "输入用户名+密码" << std::endl;
    std::cin >> n >> q;
    m_user.insert(std::pair<std::string, std::string>(n, q));

    if(sql.insert_data(m_user))
    {
        LOG(INFO) << "数据插入完成";
    }
    else
    {
        LOG(ERROR) << "数据插入错误";
    }

    std::string data_username;
    std::cout << "输入要删除的用户" << std::endl;
    std::cin >> data_username;
    if(sql.delete_data(data_username))
    {
        LOG(INFO) << "删除用户: " << data_username << "成功";
    }

    if(!sql.search_data())
    {
        LOG(ERROR) << "查询失败";
    }

    return 0;
}
