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
    else if(start == 'Y') //main
    {
        cout << "loading----------" << endl;
        Game User;
        User.Game_set_map(); //框架图
        bool flag_move = true;
        while(flag_move)
        {
            User.Game_set_randnum();
            char move;
            cin >> move;
            flag = User.Game_set_move(move);
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
