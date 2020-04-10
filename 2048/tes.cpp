#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include <termios.h>
using namespace std;

#define max_x 8
#define max_y 4
int map_size[max_x][max_y];

void drawline()
{
    int x, y;
    system("clear");

    for(x = 0; x < max_x; ++x)
    {
        for(y = 0; y < max_y; ++y)
        {
            if(map_size[x][y] == 1)
            {
                cout << " ———";
            }
            else if(map_size[x][y] == 2)
            {
                cout << "  | ";
            }
        }

        cout << endl;
    }
}

int main()
{
    int i, j;
    int con = 4;
    for(i = 0; i < max_x; ++i)
    {
        for(j = 0; j < max_y; ++j)        
        {
            if(i % 2 == 0)
            {
                map_size[i][j] = 1;
            }
            else if(i %2 == 1)
            {
                map_size[i][j] = 2;
            }
        }
    }

    drawline();
}
