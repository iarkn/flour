#include "player.h"

void player_set_pos(struct Player *player, int x, int y)
{
    player->x = x;
    player->y = y;
}
