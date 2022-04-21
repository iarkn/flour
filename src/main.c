#include "game.h"
#include "renderer.h"

#include <locale.h>
#include <stdbool.h>

int main(void)
{
    setlocale(LC_ALL, "C.UTF-8");

    game_init(150, 90, 420);
    renderer_init();

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

    renderer_free();
    game_free();

    return 0;
}
