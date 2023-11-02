#include "GameElements.h"

////////////////////////////////////////////////////////////////////////////////
// Map2D
////////////////////////////////////////////////////////////////////////////////

size_t Map2D::positionToMapIndex(float map_x, float map_y) {

    int num_col = static_cast<int> (map_x);
    int num_row = static_cast<int> (map_y);

    size_t index_in_map = ((num_row * MAP_WIDTH ) +  num_col) * 2;

    return index_in_map;
}


bool Map2D::isWall(float x, float y) {

    size_t index_in_map = positionToMapIndex(x, y);

    bool is_wall = false;

    char target_cell = *(_base_map + index_in_map);

    if (target_cell == MINIMAP_WALL_CHARACTER) {

        is_wall = true;
    }

    return is_wall;
}


bool Map2D::isGhostRoom(float x, float y) {

    size_t index_in_map = positionToMapIndex(x, y);

    bool is_ghost_room = false;

    char target_cell = *(_base_map + index_in_map);

    if (target_cell == MINIMAP_GHOST_ROOM_CHARACTER ||
        target_cell == MINIMAP_DOOR_CHARACTER) {

        is_ghost_room = true;
    }

    return is_ghost_room;
}