#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>

struct Player {
    int x;
    int y;
};

void player_set_pos(struct Player *player, int x, int y);
void player_write(const struct Player *player, FILE *file);
void player_read(struct Player *player, FILE *file);

#endif // PLAYER_H
