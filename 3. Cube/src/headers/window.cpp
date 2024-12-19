#include <iostream>
#include <SDL2/SDL.h>
#include "window.hpp"

State state;

void init_window(void) {
    // Init Test
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }
    
    // Init Window
    state.window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1), 1024, 768, SDL_WINDOW_SHOWN);
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
        }
    }
}

void pixel(float x, float y) {
    state.points.emplace_back(SDL_FPoint{x,y});
}

void line(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy,dx);
    
    for (float i = 0; i < length; i++) {
        pixel(x1 + std::cos(angle) * i, y1 + std::sin(angle) * i);
    }
}

void show() {
    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);

    SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
    for (auto &point : state.points) {
        SDL_RenderDrawPointF(state.renderer, point.x, point.y);
    }
    SDL_RenderPresent(state.renderer);
}

void rotate(vec3 &point, float x, float y, float z) {
    float rad = 0;

    rad = x;
    point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
    point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

    rad = y;
    point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;
    
    rad = z;
    point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
    point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;
}

void clear() {
    state.points.clear();
}