#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "headers/window.hpp"

int main(void) {

    init_window();
    std::vector<vec3> points {
        {500, 300, 400},
        {500, 300, 700}
    };
    std::vector<vec3> points2 {
        {300, 400, 600},
        {600, 100, 200}
    };

    // Window Loop
    while(state.isRunning) {
        for(auto &p : points) {
            rotate(p, 0.003, 0.005, 0.003);
        }
        for(auto &p : points2) {
            rotate(p, 0.001, 0.003, 0.008);
        }
        for(auto &p : points) {
            pixel(p.x, p.y);
        }
        for(auto &p : points2) {
            pixel(p.x, p.y);
        }

        event_processor();
        show();
    }

    close_window();

    return 0;
}