#ifndef RENDERER_H
#define RENDERER_H

#include <ncurses.h>

typedef struct {
    int width;
    int height;
    int x, y;
} Camera;

typedef struct {
    WINDOW *main;
    int max_rows;
    int max_cols;
} Renderer;

void renderer_init(void);
void renderer_free(void);
void renderer_draw(void);

#endif // RENDERER_H
