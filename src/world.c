#include "world.h"

#include "simplex.h"

#include <stdlib.h>

void world_init(struct World *world, int width, int height)
{
    world->width = width;
    world->height = height;
    world->tiles = realloc(world->tiles, width * height * sizeof(world->tiles[0]));
}

void world_free(struct World *world)
{
    free(world->tiles);
}

void world_gen(struct World *world, int seed)
{
    world->seed = seed;
    float scale = 12.3f;

    for (int i = 0; i < world->width * world->height; ++i) {
        float x = i % world->width, y = i / world->width;
        float n = simplex_noise2d(x / scale, y / scale, seed);

        if (n > 0.4f) world->tiles[i] = TILE_NOT_EMPTY;
    }
}

int world_get_tile(const struct World *world, int x, int y)
{
    if (x >= 0 && x < world->width && y >= 0 && y < world->height) {
        return world->tiles[world->width * y + x];
    }
    return -1;
}
