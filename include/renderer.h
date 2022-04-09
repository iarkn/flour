#ifndef RENDERER_H
#define RENDERER_H

#include <ncurses.h>

struct Camera {
    int w, h;
    int x, y;
};

struct Renderer {
    WINDOW *main;
    int max_rows;
    int max_cols;
};

void renderer_init(void);
void renderer_free(void);
void renderer_draw(void);

#endif // RENDERER_H
