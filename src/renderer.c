#include "renderer.h"

#include "game.h"
#include "math/umath.h"

#define CAMERA_BORDER_OFFSET 2

struct Camera camera;
struct Renderer renderer;

static void camera_update(void)
{
    getmaxyx(renderer.main, camera.h, camera.w);

    camera.w -= CAMERA_BORDER_OFFSET;
    camera.h -= CAMERA_BORDER_OFFSET;

    int cw = camera.w;
    int ch = camera.h;
    struct Player p = game.player;

    camera.x = clamp(p.x - cw / 2, 0, game.world.width - cw);
    camera.y = clamp(p.y - ch / 2, 0, game.world.height - ch);

#ifdef DEBUG
    move(LINES - 3, 0);
    clrtobot();
    mvprintw(LINES - 3, 0, "world: %dx%d",
             game.world.width, game.world.height);
    mvprintw(LINES - 2, 0, "player: (%d,%d) (scr %d,%d)",
             p.x, p.y, p.x - camera.x, p.y - camera.y);
    mvprintw(LINES - 1, 0, "camera: (%d,%d) (mid %d,%d) %dx%d",
             camera.x, camera.y, cw / 2, ch / 2, cw, ch);
#endif
}

void renderer_init(void)
{
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    noecho();
    cbreak();

    getmaxyx(stdscr, renderer.max_rows, renderer.max_cols);
    renderer.main = newwin(renderer.max_rows / 1.5, renderer.max_cols, 0, 0);

    camera_update();
}

void renderer_free(void)
{
    endwin();
    delwin(renderer.main);
}

void renderer_draw(void)
{
    struct Player p = game.player;
    WINDOW *win = renderer.main;

    camera_update();

    int width = camera.w;
    int height = camera.h;

    werase(win);

    for (int i = 0; i < width * height; ++i) {
        int x = i % width, y = i / width;
        int dx = x + camera.x;
        int dy = y + camera.y;

#ifdef DEBUG
        mvwaddstr(win, height - y, x + 1, ".");
        mvwaddstr(win, height - height / 2, width / 2 + 1, "@");
#endif

        if (dx == p.x && dy == p.y) {
            mvwaddstr(win, height - y, x + 1, "ඞ");
        } else if (world_get_tile(&game.world, dx, dy) == TILE_NOT_EMPTY) {
            mvwaddstr(win, height - y, x + 1, "#");
        }
    }

    box(win, 0, 0);
    refresh();
    wrefresh(win);
}
