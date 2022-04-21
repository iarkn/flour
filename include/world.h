#ifndef WORLD_H
#define WORLD_H

// TODO: Remove placeholder tile enum
enum Tile {
    TILE_EMPTY = 0,
    TILE_NOT_EMPTY
};

struct World {
    int width;
    int height;
    int *tiles;
    int seed;
};

void world_init(struct World *world, int width, int height);
void world_free(struct World *world);
void world_gen(struct World *world, int seed);
int world_get_tile(const struct World *world, int x, int y);

#endif // WORLD_H
