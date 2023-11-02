#include "GameEngine.h"

#include <ncursesw/ncurses.h>
#include <locale.h>



void GameEngine::run() {

    initEngine();

    runGameLoop();

    cleanAndClose();
}


void GameEngine::initEngine() {

    // Set the system locale to UTF-8 to use UNICODE.
    setlocale(LC_ALL, "");

    // Initialize ncurses.
    initscr(); 

    // Hide cursor.
    curs_set(0); 

    // Enable color support.
    start_color(); 

    // Set a 100 milliseconds timeout for getch.
    timeout(100);

    // Set getch to non-blocking mode
    nodelay(stdscr, TRUE); 

    // Define color pairs (you can define your own color pairs)
    // Pair n, Letter color, background color
    init_pair(TEXT_COLOR_RED_OVER_BLACK, COLOR_RED, COLOR_BLACK); 
    init_pair(TEXT_COLOR_BLUE_OVER_BLACK, COLOR_BLUE, COLOR_BLACK); 
    init_pair(TEXT_COLOR_YELLOW_OVER_BLACK, COLOR_YELLOW, COLOR_BLACK); 
    init_pair(TEXT_COLOR_MAGENTA_OVER_BLACK, COLOR_MAGENTA, COLOR_BLACK); 
    init_pair(TEXT_COLOR_GREEN_OVER_BLACK, COLOR_GREEN, COLOR_BLACK); 
    init_pair(TEXT_COLOR_WHITE_OVER_BLACK, COLOR_WHITE, COLOR_BLACK); 
    init_pair(TEXT_COLOR_CYAN_OVER_BLACK, COLOR_CYAN, COLOR_BLACK); 
    init_pair(TEXT_COLOR_CYAN_OVER_CYAN, COLOR_CYAN, COLOR_CYAN); 

    // Setup matrix for coins.
    for (int num_row = 1; num_row < MAP_HEIGHT - 1; num_row++) {

        for (int num_col = 1; num_col < MAP_WIDTH - 1; num_col++) {

            if (!_map_2d.isWall(num_col, num_row) && 
                !_map_2d.isGhostRoom(num_col, num_row)) {

                _cell_has_coin[num_row][num_col] = true;
            }
            else{

                _cell_has_coin[num_row][num_col] = false;
            }
        }
    }
}


void GameEngine::runGameLoop() {

    while(_key_pressed != KEY_PRESSED_QUIT) {

        readKeyboardInput();

        runLogic();

        drawFrame();
    }
}


void GameEngine::runLogic() {

    

}


void GameEngine::readKeyboardInput() {

    switch(getch()) {

        // No key pressed.
        case ERR: 
            _key_pressed = KEY_PRESSED_NONE;
            break;

        // Left press.
        case 'a':
        case KEY_LEFT:
            _key_pressed = KEY_PRESSED_LEFT;
            break;
        
        // Right press.
        case 'd':
        case KEY_RIGHT:
            _key_pressed = KEY_PRESSED_RIGHT;
            break;

        // Up press.
        case 'w':
        case KEY_UP:
            _key_pressed = KEY_PRESSED_UP;
            break;
        
        // Right press.
        case 's':
        case KEY_DOWN:
            _key_pressed = KEY_PRESSED_DOWN;
            break;

        // Pause press.
        case ' ':
            _key_pressed = KEY_PRESSED_PAUSE;
            break;

        // Right press.
        case 'q':
        case 27:
            _key_pressed = KEY_PRESSED_QUIT;
            break;
        
        // Any other (invalid) keys.
        default:
            _key_pressed = KEY_PRESSED_NONE;
    }

    refresh();
}


void GameEngine::drawMiniMap() {

    size_t pointer_offset = 0;

    for (int num_row = 0; num_row < MAP_HEIGHT; num_row++) {

        // Draws each cell of the 2D mini map.
        for (int num_col = 0; num_col < MAP_WIDTH; num_col++) {

            const char* char_to_draw = _map_2d._base_map + pointer_offset;

            if (*char_to_draw == MINIMAP_WALL_CHARACTER) {

                mvaddch(num_row, 2 * num_col, ' ' | COLOR_PAIR(TEXT_COLOR_CYAN_OVER_CYAN)); 
                mvaddch(num_row, 2 * num_col + 1, ' ' | COLOR_PAIR(TEXT_COLOR_CYAN_OVER_CYAN)); 
            }
            else if (*char_to_draw == MINIMAP_DOOR_CHARACTER) {
                
                attron(A_BOLD);
                mvaddch(num_row, 2 * num_col, MINIMAP_DOOR_CHARACTER | COLOR_PAIR(TEXT_COLOR_CYAN_OVER_BLACK)); 
                mvaddch(num_row, 2 * num_col + 1, MINIMAP_DOOR_CHARACTER | COLOR_PAIR(TEXT_COLOR_CYAN_OVER_BLACK)); 
                attroff(A_BOLD); 
            }
            else if(_cell_has_coin[num_row][num_col]) { // Draw coin

                attron(A_BOLD);
                mvaddch(num_row, 2 * num_col, '<' | COLOR_PAIR(TEXT_COLOR_WHITE_OVER_BLACK));
                mvaddch(num_row, 2 * num_col + 1, '>' | COLOR_PAIR(TEXT_COLOR_WHITE_OVER_BLACK));
                attroff(A_BOLD); 
            }
            else {

                mvaddch(num_row, 2 * num_col, ' ');
                mvaddch(num_row, 2 * num_col + 1, ' ');
            }
            pointer_offset += 2;
        }
    }

    if (_gate_closed) {
        
        mvaddch(6, 14, ' ' | COLOR_PAIR(TEXT_COLOR_CYAN_OVER_BLACK)); 
        mvaddch(6, 15, ' ' | COLOR_PAIR(TEXT_COLOR_CYAN_OVER_BLACK)); 
        mvaddch(6, 16, ' ' | COLOR_PAIR(TEXT_COLOR_CYAN_OVER_BLACK)); 
        mvaddch(6, 17, ' ' | COLOR_PAIR(TEXT_COLOR_CYAN_OVER_BLACK));
    }

    // Draw the ghosts
    drawGhostInMinimap(9, 7, TEXT_COLOR_RED_OVER_BLACK);
    drawGhostInMinimap(6, 7, TEXT_COLOR_MAGENTA_OVER_BLACK);
    drawGhostInMinimap(6, 8, TEXT_COLOR_GREEN_OVER_BLACK);
    drawGhostInMinimap(9, 8, TEXT_COLOR_BLUE_OVER_BLACK);

    drawHero(7.5, 10);
}


void GameEngine::drawHero(float x, float y) {

    
    int x_map = 2 * static_cast<int> (x);
    int y_map = static_cast<int> (y);
     
    // Enable the A_BOLD attribute
    attron(A_BOLD);

    // Select the color.
    attron(COLOR_PAIR(TEXT_COLOR_YELLOW_OVER_BLACK));
    mvaddwstr(y_map, x_map, L"ᕮᕭ");
    
    // Disables the color.
    attroff(COLOR_PAIR(TEXT_COLOR_YELLOW_OVER_BLACK));
    // Disable the A_BOLD attribute
    attroff(A_BOLD);
}


void GameEngine::drawGhostInMinimap(float x, float y, TextColor text_color) {

    int x_map = 2 * static_cast<int> (x);
    int y_map = static_cast<int> (y);

    // Enable the A_BOLD attribute
    attron(A_BOLD);
    if (text_color != TEXT_COLOR_DEFAULT) {

        mvaddch(y_map, x_map, 'I' | COLOR_PAIR(text_color));
        mvaddch(y_map, x_map + 1, 'I' | COLOR_PAIR(text_color));
    }
    else {
        mvaddch(y_map, x_map, 'I');
        mvaddch(y_map, x_map + 1, 'I');
    }

    // Disable the A_BOLD attribute
    attroff(A_BOLD);
}


void GameEngine::drawFrame() {

    drawMiniMap();



    refresh(); // Refresh the screen
}


void GameEngine::cleanAndClose() {

    getch(); // Wait for user input
    endwin(); // Clean up and exit ncurses
}
