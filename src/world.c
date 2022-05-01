#include "world.h"

#include "item.h"
#include "util/simplex.h"

#include <stdlib.h>
#include <string.h>

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

void world_clear(struct World *world)
{
    for (int i = 0; i < world->width * world->height; ++i) {
        int x = i % world->width, y = i / world->width;
        world->tiles[world->width * y + x] = tiles[TILE_FLOOR];
    }
}

void world_gen(struct World *world, int seed)
{
    world->seed = seed;
    float scale = 12.3f;

    world_clear(world);

    for (int i = 0; i < world->width * world->height; ++i) {
        float x = i % world->width, y = i / world->width;
        float n = simplex_noise2d(x / scale, y / scale, seed);

        if (n > 0.4f) world->tiles[i] = tiles[TILE_WALL];
    }
}

struct Tile *world_get_tile(struct World *world, int x, int y)
{
    if (x >= 0 && x < world->width && y >= 0 && y < world->height) {
        return &world->tiles[world->width * y + x];
    }
    return NULL;
}

void world_write(const struct World *world, FILE *file)
{
    fwrite(&world->width, sizeof(world->width), 1, file);
    fwrite(&world->height, sizeof(world->height), 1, file);
    fwrite(&world->seed, sizeof(world->seed), 1, file);

    for (int i = 0; i < world->width * world->height; ++i) {
        int x = i % world->width, y = i / world->width;
        int id = world->tiles[world->width * y + x].id;

        fwrite(&id, sizeof(id), 1, file);
    }
}

void world_read(struct World *world, FILE *file)
{
    fread(&world->width, sizeof(world->width), 1, file);
    fread(&world->height, sizeof(world->height), 1, file);
    fread(&world->seed, sizeof(world->seed), 1, file);

    int size = world->width * world->height;
    world->tiles = realloc(world->tiles, size * sizeof(world->tiles[0]));

    for (int i = 0; i < size; ++i) {
        int x = i % world->width, y = i / world->width;
        int id;

        fread(&id, sizeof(id), 1, file);
        world->tiles[world->width * y + x] = tiles[id];
    }
}
