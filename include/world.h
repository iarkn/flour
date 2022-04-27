#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>

enum TileAttr {
    TILE_ATTR_NONE  = 0,
    TILE_ATTR_SOLID = 1 << 0
};

struct Tile {
    char *icon;
    int attr;
    int id;
};

struct World {
    int width;
    int height;
    int seed;
    struct Tile *tiles;
};

void world_init(struct World *world, int width, int height);
void world_free(struct World *world);
void world_clear(struct World *world);
void world_gen(struct World *world, int seed);
struct Tile *world_get_tile(struct World *world, int x, int y);
void world_write(const struct World *world, FILE *file);
void world_read(struct World *world, FILE *file);

#endif // WORLD_H
