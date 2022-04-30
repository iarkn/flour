#include "item.h"

#define ADD_TILE(_id, _icon, _attr) \
    [_id] = { .icon = _icon, .attr = _attr, .id = _id }

const struct Tile tiles[] = {
    ADD_TILE(TILE_FLOOR, "", TILE_ATTR_NONE),
    ADD_TILE(TILE_WALL, "#", TILE_ATTR_SOLID)
};
