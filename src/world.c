#include "world.h"

#include <stdlib.h>

void world_init(World *world, int width, int height)
{
    world->width = width;
    world->height = height;
    world->tiles = calloc(sizeof(world->tiles[0]), width * height);
}

void world_free(World *world)
{
    free(world->tiles);
}

int world_get_tile(const World *world, int x, int y)
{
    if (x >= 0 && x < world->width && y >= 0 && y < world->height) {
        return world->tiles[world->width * y + x];
    }
    return -1;
}
