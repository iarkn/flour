#include "player.h"

void player_set_pos(struct Player *player, int x, int y)
{
    player->x = x;
    player->y = y;
}

void player_write(const struct Player *player, FILE *file)
{
    fwrite(&player->x, sizeof(player->x), 1, file);
    fwrite(&player->y, sizeof(player->y), 1, file);
}

void player_read(struct Player *player, FILE *file)
{
    fread(&player->x, sizeof(player->x), 1, file);
    fread(&player->y, sizeof(player->y), 1, file);
}
