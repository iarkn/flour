#include "game.h"

struct Game game;

void game_init(int width, int height)
{
    world_init(&game.world, width, height);

    game.player.x = width / 2;
    game.player.y = height / 2;
}

void game_free(void)
{
    world_free(&game.world);
}

void game_move_player(int x, int y)
{
    x += game.player.x;
    y += game.player.y;

    if (world_get_tile(&game.world, x, y) == TILE_EMPTY) {
        player_set_pos(&game.player, x, y);
    }
}
