#include <iostream>
#include <SDL2/SDL.h>
#include "headers/window.hpp"

int main(void) {

    init_window();
    // Window Loop
    while(state.isRunning) {
        event_processor();
        render();
    }

    close_window();

    return 0;
}