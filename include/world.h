#ifndef WORLD_H
#define WORLD_H

typedef struct {
    int width;
    int height;
    int *tiles;
} World;

void world_init(World *world, int width, int height);
void world_free(World *world);
int world_get_tile(const World *world, int x, int y);

#endif // WORLD_H
