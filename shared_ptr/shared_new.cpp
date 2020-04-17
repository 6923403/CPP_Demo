#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

void test1()
{
    int *ip = new int(42);
    /*
     * ex out_rang
     * not delete
     */
    delete ip;
}

void test2()
{
    shared_ptr<int> sp(new int(42));
    //use sp
    //auto delete
}

void end_connection(connection *p)
{
    disconnect(*p);
}
/*
void test3()
{
    struct destination;
    struct connection;
    connection connect(destination *);
    void disconnect(connection);

    void f(destination &d)
    {
        connection c = connect(&d);
        shared_ptr<connection> p(&c, end_connection);
    }
}*/

int main(int argc, char **argv)
{
    test2();
}