#include <iostream>
#include <string>
using namespace std;

void test1()
{
    double *pvalue = NULL;
    pvalue = new double;

    *pvalue = 294.99;
    cout << "Pvalue" << *pvalue << endl;

    delete pvalue;
}

void test2()
{
    int m = 7;
    //一维
    int *array = new int[m]{1, 5, 10, 9, 3, 6};
    for(int s; s < m; s++)
        cout <<  array[s] << endl;

    delete []array;
}

void test3()
{
    int **p;
    int i, j;
    p = new int *[4];
    for(i = 0; i < 4; i++)
    {
        p[i] = new int[8];
    }

    for(i = 0; i < 4; i++)
        for(j = 0; j < 8; j++)
        {
            if(j == 0)
                cout << endl;
            cout << p[i][j] << "\t";
        }

    for(i = 0; i < 4; i++)
    {
        delete []p[i];

    }

    delete []p;

}

int main(int argc, char **argv)
{
    test3();
}
