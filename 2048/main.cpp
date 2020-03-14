#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include "game.h"
using namespace std;

int main(int argc, char **argv) //6*6
{
    cout << 
    "              \n" <<
    "--------2048--------\n" << 
    "-------start-------\n" << endl;

    char start;
    bool flag = true;

    while(flag)    {
        flag = false;
    cout << "Y or N" << endl;
    cin >> start;
    if(start == 'N')
    {
        cout << "Bye~" << endl;
        exit(-1);
    }
    else if(start == 'Y')
    {
        cout << "loading----------" << endl;
        Game User(0, 13);
        //int size = get_map_size();
        User.Game_set_map(); //框架图

        bool lis = true;
        char mv;
        while(lis)
        {
            User.Game_set_randnum();
            cin >> mv;
            if(mv == 'q')
            {
                break;
                lis = false;
            }

            User.Game_set_map(); //框架图
        }

    }
    else
    {
        cout << "Please re-input " << endl;
        flag = true;
    }
 }

    return 0;
}
