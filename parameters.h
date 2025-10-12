#ifndef GRAPHICS_H
#define GRAPHICS_H

//states
enum State {
    menu,
    help,
    records,
    game
};

enum Result {
    win,
    lose,
    def
};

//window
#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1000

//colors
#define BARNRED (Color){120, 0, 0, 255}
#define FIREBRICK (Color){193, 18, 31, 255}
#define PAPAYAWHIP (Color){253, 240, 213, 255}
#define PRUSSIANBLUE (Color){0, 48, 73, 255}
#define AIRSUPERIORITYBLUE (Color){102, 155, 188, 255}
#define GRAYISHBLUE (Color){177, 197, 200, 255}

#endif
