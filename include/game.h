#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "world.h"

#include <stdbool.h>

struct Game {
    struct World world;
    struct Player player;
};

// global
extern struct Game game;

void game_init(int width, int height, int seed);
void game_free(void);
bool game_save(const char *path);
bool game_load(const char *path);
void game_move_player(int x, int y);

#endif // GAME_H
