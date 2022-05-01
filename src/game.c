#include "game.h"

#include "util/gzip.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

struct Game game;

const int file_sign = 0xded42069;

void game_init(int width, int height, int seed)
{
    world_init(&game.world, width, height);
    world_gen(&game.world, seed);
}

void game_free(void)
{
    world_free(&game.world);
}

bool game_save(const char *path)
{
    FILE *tmp = tmpfile();
    FILE *file = fopen(path, "w");
    if (!file) {
        fprintf(stderr, "game_save: failed to open file '%s': %s\n",
                path, strerror(errno));
        return false;
    }

    fwrite(&file_sign, 1, sizeof(file_sign), tmp);
    world_write(&game.world, tmp);
    player_write(&game.player, tmp);
    rewind(tmp);

    bool ret = true;
    if (gzip_c(gzip_def(tmp, file, -1))) {
        fprintf(stderr, "game_save: failed to compress file '%s'\n", path);
        ret = false;
    }

    fclose(tmp);
    fclose(file);

    return ret;
}

bool game_load(const char *path)
{
    FILE *tmp = tmpfile();
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "game_load: failed to open file '%s': %s\n",
                path, strerror(errno));
        return false;
    }

    if (gzip_c(gzip_inf(file, tmp))) {
        fprintf(stderr, "game_load: failed to decompress file '%s'\n", path);
        return false;
    }

    bool ret = true;
    int sign;

    rewind(tmp);
    fread(&sign, 1, sizeof(sign), tmp);
    if (sign == file_sign) {
        world_read(&game.world, tmp);
        player_read(&game.player, tmp);
    } else {
        fprintf(stderr, "game_load: wrong file signature in file '%s'\n", path);
        ret = false;
    }

    fclose(tmp);
    fclose(file);

    return ret;
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
