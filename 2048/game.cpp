#include <iostream>
#include "game.h"
using namespace std;

Game::Game(int p1, int p2)
{
    int i, j;
    for(i = 0; i < rows; ++i)
        for(j = 0; j < cols; ++j)
            map_size[i][j] = 0;

    map_size[p1/cols][p1%cols] = 2;
    map_size[p2/cols][p2%cols] = 2;
}

void Game::Game_set_randnum()
{

}


void Game::Game_set_map()
{
#if 0
    int L = 8;
    int cols = size;
    int rows = size; 
#endif
    int i, j, k;
    for(i = 0; i < L * cols; ++i)
    {
        cout << "-";
    }
    cout << endl;

    for(i = 0; i < rows; ++i)
    {
       cout << "|";
       for(j = 0; j < cols; ++j)
       {
           cout.width(L);
          /* //k = map_size[i][j];
           cout.width(L);
           if(k)
               cout << k;
           else
               cout << "";
               */
           cout << "|";
       }
       cout << endl;
    }
    for(i = 0; i <= (L + 1) * cols; ++i)
        cout << "-";
    cout << endl;

}

int get_map_size()
{
begin:
    cout << "Set Map_size: 4/5/6/7" << endl;
    int set_size;
    cin >> set_size;

    if(set_size > 3 && set_size < 8)
        return set_size;
    else
    {
        cout << "please re-input" << endl;
        goto begin;
    }
}
