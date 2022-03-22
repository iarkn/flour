#include "game.h"
#include "renderer.h"

#include <locale.h>
#include <stdbool.h>

int main(void)
{
    setlocale(LC_ALL, "C.UTF-8");

    game_init(80, 50);
    renderer_init();

    for (int y = 2; y < 5; ++y)
        for (int x = 8; x < 22; ++x)
            game.world.tiles[game.world.width * y + x] = TILE_NOT_EMPTY;

    for (int y = 20; y < 27; ++y)
        for (int x = 14; x < 26; ++x)
            game.world.tiles[game.world.width * y + x] = TILE_NOT_EMPTY;

    for (int y = 13; y < 19; ++y)
        for (int x = 2; x < 12; ++x)
            game.world.tiles[game.world.width * y + x] = TILE_NOT_EMPTY;

    for (int y = 8; y < 16; ++y)
        for (int x = 34; x < 47; ++x)
            game.world.tiles[game.world.width * y + x] = TILE_NOT_EMPTY;

    int c;
    bool quit = false;

    while (!quit) {
        renderer_draw();

        switch (c = getch()) {
        case KEY_UP:
        case 'w':
            game_move_player(0, 1);
            break;
        case KEY_DOWN:
        case 's':
            game_move_player(0, -1);
            break;
        case KEY_LEFT:
        case 'a':
            game_move_player(-1, 0);
            break;
        case KEY_RIGHT:
        case 'd':
            game_move_player(1, 0);
            break;
        case 'q':
            quit = true;
            break;
        default:
            break;
        }
    }

    endwin();

    renderer_free();
    game_free();

    return 0;
}
