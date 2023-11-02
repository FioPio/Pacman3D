
#pragma once

#include "GameElements.h"

enum TextColor {

    TEXT_COLOR_DEFAULT = 0,
    TEXT_COLOR_RED_OVER_BLACK = 1,
    TEXT_COLOR_BLUE_OVER_BLACK = 2,
    TEXT_COLOR_YELLOW_OVER_BLACK = 3,
    TEXT_COLOR_MAGENTA_OVER_BLACK = 4,
    TEXT_COLOR_GREEN_OVER_BLACK = 5,
    TEXT_COLOR_WHITE_OVER_BLACK = 6,
    TEXT_COLOR_CYAN_OVER_BLACK = 7,
    TEXT_COLOR_CYAN_OVER_CYAN = 8
};

enum KeyPressed {

    KEY_PRESSED_NONE,
    KEY_PRESSED_UP,
    KEY_PRESSED_DOWN,
    KEY_PRESSED_LEFT,
    KEY_PRESSED_RIGHT,
    KEY_PRESSED_PAUSE,
    KEY_PRESSED_QUIT
};


class GameEngine {

public:

    void run();

private:

    Map2D _map_2d;

    bool _gate_closed{false};

    KeyPressed _key_pressed{KEY_PRESSED_NONE};

    bool _cell_has_coin[MAP_WIDTH][MAP_HEIGHT];


    void initEngine();

    void runGameLoop();

    void runLogic();

    void readKeyboardInput();

    void drawMiniMap();

    void drawHero(float x, float y);

    void drawGhostInMinimap(float x, float y, TextColor text_color);

    void drawFrame();

    void cleanAndClose();

};
