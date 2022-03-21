#include "renderer.h"

#include "game.h"
#include "umath.h"

#define BORDER_OFFSET 2

Camera camera;
Renderer renderer;

static void camera_update(void)
{
    getmaxyx(renderer.main, camera.height, camera.width);

    camera.width -= BORDER_OFFSET * 2;
    camera.height -= BORDER_OFFSET;
    camera.x = clampi(game.player.x - camera.width / 2, 0, game.world.width);
    camera.y = clampi(game.player.y - camera.height / 2, 0, game.world.height - camera.height);
}

void renderer_init(void)
{
    getmaxyx(stdscr, renderer.max_rows, renderer.max_cols);
    renderer.main = newwin(renderer.max_rows / 1.5, renderer.max_cols, 0, 0);
}

void renderer_free(void)
{
    delwin(renderer.main);
}

void renderer_draw(void)
{
    Player *p = &game.player;
    WINDOW *win = renderer.main;

    camera_update();

    int width = camera.width;
    int height = camera.height;

    werase(win);

    for (int i = 0; i < width * height; ++i) {
        int x = i % width, y = i / width;
        int dx = x + camera.x;
        int dy = y + camera.y;

        if (dx == p->x && dy == p->y) {
            mvwaddstr(win, height - y, 2 * x + 1, "██");
        } else if (world_get_tile(&game.world, dx, dy) == 1) {
            mvwaddstr(win, height - y, 2 * x + 1, "##");
        }
    }

    box(win, 0, 0);
    refresh();
    wrefresh(win);
}
