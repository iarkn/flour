#include "game.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

struct Game game;

void game_init(int width, int height, int seed)
{
    world_init(&game.world, width, height);
    world_gen(&game.world, seed);
}

void game_free(void)
{
    world_free(&game.world);
}

// TODO: Deflate the save file for no reason using gzip
bool game_save(const char *path)
{
    FILE *file = fopen(path, "w");
    if (!file) {
        fprintf(stderr, "error: game_save: failed to open file '%s': %s\n",
                path, strerror(errno));
        return false;
    }

    world_write(&game.world, file);
    player_write(&game.player, file);
    fclose(file);

    return true;
}

bool game_load(const char *path)
{
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "error: game_load: failed to open file '%s': %s\n",
                path, strerror(errno));
        return false;
    }

    world_read(&game.world, file);
    player_read(&game.player, file);
    fclose(file);

    return true;
}

void game_move_player(int x, int y)
{
    x += game.player.x;
    y += game.player.y;

    const struct Tile* tile = world_get_tile(&game.world, x, y);

    if (tile && tile->attr == TILE_ATTR_NONE) {
        player_set_pos(&game.player, x, y);
    }
}
