#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "world.h"

typedef struct {
    World world;
    Player player;
} Game;

// global
extern Game game;

void game_init(int width, int height);
void game_free(void);
void game_move_player(int x, int y);

#endif // GAME_H
