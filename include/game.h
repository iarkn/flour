#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "world.h"

struct Game {
    struct World world;
    struct Player player;
};

// global
extern struct Game game;

void game_init(int width, int height);
void game_free(void);
void game_move_player(int x, int y);

#endif // GAME_H
