#include "renderer.h"

#include "game.h"
#include "util/math.h"

struct Camera {
    int w, h;
    int x, y;
};

struct Renderer {
    WINDOW *main;
    WINDOW *hud;
    int max_rows;
    int max_cols;
};

struct Camera camera;
struct Renderer renderer;

static void camera_update(void)
{
    getmaxyx(renderer.main, camera.h, camera.w);

    int cw = camera.w;
    int ch = camera.h;
    struct Player p = game.player;

    camera.x = clamp(p.x - cw / 2, 0, max(game.world.width - cw, 0));
    camera.y = clamp(p.y - ch / 2, 0, max(game.world.height - ch, 0));
}

void renderer_init(void)
{
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    noecho();
    cbreak();

    getmaxyx(stdscr, renderer.max_rows, renderer.max_cols);
    renderer.main = newwin(renderer.max_rows, renderer.max_cols, 0, 0);
    renderer.hud = newwin(renderer.max_rows, renderer.max_cols, 0, 0);
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
    WINDOW *hud = renderer.hud;

    camera_update();

    werase(win);
    werase(hud);
    wnoutrefresh(win);
    wnoutrefresh(hud);
    wnoutrefresh(stdscr);

    int width = camera.w;
    int height = camera.h;
    for (int i = 0; i < width * height; ++i) {
        int x = i % width, y = i / width;
        int dx = x + camera.x;
        int dy = y + camera.y;

#ifdef DEBUG
        mvwaddstr(win, height - y - 1, x, ".");
        mvwaddstr(win, height - height / 2 - 1, width / 2, "@");
#endif

        const struct Tile *tile = world_get_tile(&game.world, dx, dy);
        if (tile) mvwaddstr(win, height - y - 1, x, tile->icon);
    }

    wnoutrefresh(win);

#ifdef DEBUG
    mvprintw(LINES - 3, 0, "world: %dx%d",
             game.world.width, game.world.height);
    mvprintw(LINES - 2, 0, "player: (%d,%d) (scr %d,%d)",
             p.x, p.y, p.x - camera.x, p.y - camera.y);
    mvprintw(LINES - 1, 0, "camera: (%d,%d) (mid %d,%d) %dx%d",
             camera.x, camera.y, width / 2, height / 2, width, height);
    wnoutrefresh(stdscr);
#endif

    mvwaddstr(win, height - 1 - p.y + camera.y, p.x - camera.x, "█");
    wnoutrefresh(win);

    mvwprintw(hud, 1, 1, "(%d, %d)", p.x, p.y);
    wnoutrefresh(hud);

    doupdate();
}
