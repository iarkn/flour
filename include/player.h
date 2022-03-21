#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x;
    int y;
} Player;

void player_set_pos(Player *player, int x, int y);

#endif // PLAYER_H
