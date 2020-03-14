#ifndef GAME_H
#define GAME_H

//6 * 6
//Up Down Left Right
//2 4 8 16 32 64 128 256 512 1024 2048
//2048 == win
//countiue?
//

#define rows 4
#define cols 4
#define L 6
int get_map_size();

class Game
{

public:

    Game(int p1, int p2);

public:
    void Game_set_map();
    void Game_set_randnum();
    void Game_set_move();

    int map_size[rows][cols];
};

#endif
