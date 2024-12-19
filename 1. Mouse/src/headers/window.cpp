#include <iostream>
#include <SDL2/SDL.h>
#include "window.hpp"

State state;
int last_frame_time = 0;

void init_window(void) {
    // Init Test
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }
    
    // Init Window
    state.window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1), 640, 480, SDL_WINDOW_SHOWN);
    state.renderer = SDL_CreateRenderer(state.window, -1, 0);
    state.isRunning = true;
    SDL_ShowCursor(SDL_DISABLE);
}

void close_window(void) {
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}

void event_processor(void) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                state.isRunning = false;
                break;
            case SDL_MOUSEMOTION:
                state.mouse_x = e.motion.x;
                state.mouse_y = e.motion.y;
                break;
        }
    }
}

void render(void) {
    SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
    SDL_RenderClear(state.renderer);

    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_Rect mouse = {state.mouse_x, state.mouse_y, 10, 10};
    SDL_RenderFillRect(state.renderer, &mouse);

    SDL_RenderPresent(state.renderer);
}

void update(void) {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));
    
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks();
}
