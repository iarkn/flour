#include "item.h"

#define TILE_CREATE(_icon, _attr, _id) { .icon = _icon, .attr = _attr, .id = _id }

const struct Tile tiles[TILE_COUNT] = {
    [TILE_FLOOR] = TILE_CREATE("", TILE_ATTR_NONE, TILE_FLOOR),
    [TILE_WALL]  = TILE_CREATE("#", TILE_ATTR_SOLID, TILE_WALL)
};
