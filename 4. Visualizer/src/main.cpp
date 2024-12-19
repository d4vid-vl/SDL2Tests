#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "headers/window.hpp"

int main(void) {

    init_window();
    std::vector<vec3> points {
        {500, 500, 500},
        {700, 500, 500},
        {600, 673.2, 500},
        {600, 586.6, 700},
    };

    std::vector<connection> connections {
        {0,1},
        {1,2},
        {2,0},

        {0,3},
        {1,3},
        {2,3},
    };

    vec3 c{0,0,0};
    for(auto &p: points) {
        c.x += p.x;
        c.y += p.y;
        c.z += p.z;
    }

    c.x /= points.size();
    c.y /= points.size();
    c.z /= points.size();

    // Window Loop
    while(state.isRunning) {
        for(auto &p : points) {
            p.x -= c.x;
            p.y -= c.y;
            p.z -= c.z;
            rotate(p, 0.003, 0.005, 0.003);
            p.x += c.x;
            p.y += c.y;
            p.z += c.z;
            pixel(p.x, p.y);
        }

        for(auto &conn: connections) {
            line(points[conn.a].x, points[conn.a].y, points[conn.b].x, points[conn.b].y);
        }
        event_processor();
        show();
        clear();
        SDL_Delay(20);
    }

    close_window();

    return 0;
}