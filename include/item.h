#ifndef ITEM_H
#define ITEM_H

#include "world.h"

enum TileItem {
    TILE_FLOOR = 0,
    TILE_WALL,
    TILE_COUNT
};

// global
extern const struct Tile tiles[TILE_COUNT];

#endif // ITEM_H
