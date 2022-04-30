#ifndef ITEM_H
#define ITEM_H

#include "world.h"

enum TileItem {
    TILE_FLOOR = 0,
    TILE_WALL
};

// global
extern const struct Tile tiles[];

#endif // ITEM_H
