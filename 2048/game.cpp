#include <iostream>
#include <termios.h>
#include <queue>
#include "game.h"
using namespace std;

Game::Game(int p1, int p2)
{
}

void Game::Game_draw_line()
{
    int x, y;
    system("clear");

    for(x = 0; x < max_x; ++x)
    {
        for(y = 0; y < max_y; ++y)
        {
            if(map_size[x][y] == 10)
            {
                cout << " ———";
            }
            else if(map_size[x][y] == 11)
            {
                cout << "  | ";
            }
        }
        cout << endl;
    }
}

void Game::Game_set_map()
{
    int i, j;
    for(i = 0; i < max_x; ++i)
    {
        for(j = 0; j < max_y; ++j)
        {
            if(i % 2 == 0)
            {
                map_size[i][j] = 10;

            }
            else if(i % 2 == 1)
            {
                map_size[i][j] = 11;

            }

        }
    }
    Game_draw_line();
}

void Game::Game_set_randnum()
{
    bool agin = true;
    int x1, y1;
    while(agin)
    {
        x1 = rand() % 7;
        y1 = rand() % 3;
        if(x1 % 2 == 0)
        {
            agin = true;
        }
        else if(map_size[x1][y1] == 11)
        {
            map_size[x1][y1] = 2;
            agin = false;
            Game_draw_line();
        }
        else
            agin = true;
    }

}

bool Game::Game_set_move_up(char move)
{
    bool flag_m = true;
    switch(move)
    {
        case 'q':
            flag_m = false;
            break;   
        case 'w':
            Game_set_move_down();
            break;
        case 'a':
            Game_set_move_left();
            break;
        case 's':
            Game_set_move_down();
            break;
        case 'd':
            Game_set_move_right();
            break;
    }
    return flag_m;
}

bool Game::Game_set_move_down(char move)
{

}

bool Game::Game_set_move_left(char move)
{
    int tmp[max_x][max_y];
    queue<int> q;
    int i, j, k, index;
    for(i = 0; i < max_x; ++i)
    {
        if(i % 2 == 1)
        {
            for(j = 0; j < max_y; ++j)
            {
                tmp[i][j] = map_size[i][j];
            }
        }
    }

}

bool Game::Game_set_move_right(char move)
{

}


