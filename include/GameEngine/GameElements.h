#pragma once

#include <string>


#define MAP_WIDTH   16 /**< Define map width of 16 tiles long. */
#define MAP_HEIGHT  16 /**< Define map height of 16 tiles long. */

#define MINIMAP_WALL_CHARACTER          '#'
#define MINIMAP_DOOR_CHARACTER          '-'
#define MINIMAP_GHOST_ROOM_CHARACTER    'X'


struct Map2D {

    static size_t positionToMapIndex(float map_x, float map_y);

    bool isWall(float x, float y);

    bool isGhostRoom(float x, float y);

    // Map 2D representation.
    static inline const char * _base_map = "################################"\
                                           "##      ##            ##      ##"\
                                           "##  ##  ##  ########  ##  ##  ##"\
                                           "##      ##            ##      ##"\
                                           "######  ##  ########  ##  ######"\
                                           "##                            ##"\
                                           "##  ##  ######----######  ##  ##"\
                                           "##  ##  ##XXXXXXXXXXXX##  ##  ##"\
                                           "##  ##  ##XXXXXXXXXXXX##  ##  ##"\
                                           "##  ##  ################  ##  ##"\
                                           "##                            ##"\
                                           "######  ##  ########  ##  ######"\
                                           "##      ##            ##      ##"\
                                           "##  ##  ##  ########  ##  ##  ##"\
                                           "##      ##            ##      ##"\
                                           "################################";

};


class GameEntity {

public:

    GameEntity(float x_pos, float y_pox);

private:

    float _x_pos;
    float _y_pos;
};