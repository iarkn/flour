#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    int x;
    int y;
};

void player_set_pos(struct Player *player, int x, int y);

#endif // PLAYER_H
