#ifndef GAME_H
#define GAME_H

//6 * 6
//Up Down Left Right
//2 4 8 16 32 64 128 256 512 1024 2048
//2048 == win
//countiue?
//
#define max_x 8
#define max_y 4
extern bool flag_move;

int get_map_size();

class Game
{

public:

    Game() = default;
    Game(int p1, int p2);
    

public:
    void Game_set_map();
    void Game_set_randnum();
    bool Game_set_move(char move);
    bool Game_set_move_down(char move);
    bool Game_set_move_up(char move);
    bool Game_set_move_right(char move);
    bool Game_set_move_left(char move);
    void Game_draw_line();

private:
    int map_size[max_x][max_y];

};

#endif
