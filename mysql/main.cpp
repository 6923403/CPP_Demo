#include <iostream>

#include "sql/Connect_Sql.h"

int main(int argc, char** argv)
{
    Connect_Sql* sql;

    std::string username = "root";
    std::string ip_addr = "localhost";
    std::string password = "Aa1248800211";
    int port = 3306;

    if(sql->connect_mysql(ip_addr, username, password, port))
    {
        std::cout << "123" << std::endl;
    }

    return 0;
}
