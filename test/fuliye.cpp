#include <iostream>
using namespace std;

int main()
{
    int n, m;
    char c[128];
    char a[128];
    char b[128];


    cin >> n;
    cin >> m;
    int num;
    for ( int i = 0 ; i < n ; ++ i )
    	for ( int j = 0 ; j < m ; ++ j )  {
    		c [i + j] += a [i] * b [j] ;
            num = i + j;
    	}

    
    for(int k = 0; k < num; k++)
        cout << c[k] << endl;

    return 0;
}
