#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "headers/window.hpp"

int main(void) {

    init_window();

    // Window Loop
    while(state.isRunning) {
        event_processor();
        show();
        clear();
        SDL_Delay(20);
    }

    close_window();

    return 0;
}