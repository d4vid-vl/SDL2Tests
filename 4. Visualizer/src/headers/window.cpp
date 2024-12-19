#include <iostream>
#include <SDL2/SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
#include "window.hpp"

State state;
int figure;
int len = 200;
int pos[3] = {200, 200, 200};
figure_state figure_s;

void init_window(void) {
    // Init Test
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }
    
    // Init Window
    state.window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1), WINDOW_HEIGHT, WINDOW_WIDTH, SDL_WINDOW_SHOWN);
    state.renderer = SDL_CreateRenderer(state.window, -1, 0);
    GUI_Init(state.window, state.renderer);
    state.isRunning = true;
    SDL_ShowCursor(SDL_DISABLE);
}

void close_window(void) {
    GUI_Close();
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
        ImGui_ImplSDL2_ProcessEvent(&e);
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
    // Check rotations
    for(auto &p : figure_s.points) {
        p.x -= figure_s.c.x;
        p.y -= figure_s.c.y;
        p.z -= figure_s.c.z;
        rotate(p, 0.003, 0.005, 0.003);
        p.x += figure_s.c.x;
        p.y += figure_s.c.y;
        p.z += figure_s.c.z;
        pixel(p.x, p.y);
    }

    for(auto &conn: figure_s.connections) {
        line(figure_s.points[conn.a].x, figure_s.points[conn.a].y, figure_s.points[conn.b].x, figure_s.points[conn.b].y);
    }

    // Check figure
    if (figure != GUI_Renderer(state.my_color, state.my_rads, &state.length, state.position) || state.length != len || state.position[0] != pos[0] || state.position[1] != pos[1]) {
        figure_s = sel_figure(GUI_Renderer(state.my_color, state.my_rads, &state.length, state.position));
    }
    figure = GUI_Renderer(state.my_color, state.my_rads, &state.length, state.position);
    len = state.length;
    pos[0] = state.position[0];
    pos[1] = state.position[1];
    pos[2] = state.position[2];

    // Draw canvas
    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);
    
    // Draw figure
    SDL_SetRenderDrawColor(state.renderer, state.my_color[0]*255, state.my_color[1]*255, state.my_color[2]*255, state.my_color[3]*255);
    for (auto &point : state.points) {
        SDL_RenderDrawPointF(state.renderer, point.x, point.y);
    }
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), state.renderer);
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

figure_state sel_figure(int figure) {
    figure_state figure_state;
    switch (figure) {
        case 0:
            figure_state.points = {
                {float(state.position[0]),                       float(state.position[1]),                          float(state.position[2])},
                {float(state.position[0]) + float(state.length), float(state.position[1]),                          float(state.position[2])},
                {float(state.position[0]) + float(state.length), float(state.position[1]) + float(state.length),    float(state.position[2])},
                {float(state.position[0]),                       float(state.position[1]) + float(state.length),    float(state.position[2])},

                {float(state.position[0]),                       float(state.position[1]),                          float(state.position[2]) + float(state.length)},
                {float(state.position[0]) + float(state.length), float(state.position[1]),                          float(state.position[2]) + float(state.length)},
                {float(state.position[0]) + float(state.length), float(state.position[1]) + float(state.length),    float(state.position[2]) + float(state.length)},
                {float(state.position[0]),                       float(state.position[1]) + float(state.length),    float(state.position[2]) + float(state.length)},
            };

            figure_state.connections = {
                {0,4},
                {1,5},
                {2,6},
                {3,7},

                {0,1},
                {1,2},
                {2,3},
                {3,0},

                {4,5},
                {5,6},
                {6,7},
                {7,4}
            };

            for(auto &p: figure_state.points) {
                figure_state.c.x += p.x;
                figure_state.c.y += p.y;
                figure_state.c.z += p.z;
            }

            figure_state.c.x /= figure_state.points.size();
            figure_state.c.y /= figure_state.points.size();
            figure_state.c.z /= figure_state.points.size();
            return figure_state;

        case 1:
            figure_state.points = {
                {float(state.position[0]),                          float(state.position[1]),                                    float(state.position[2])},
                {float(state.position[0]) + float(state.length),    float(state.position[1]),                                    float(state.position[2])},
                {float(state.position[0]) + float(state.length)/2,  float(state.position[1]) + float(state.length)*(sqrt(3)),    float(state.position[2])},
                {float(state.position[0]) + float(state.length)/2,  float(state.position[1]) + float(state.length)*(sqrt(3))/2,  float(state.position[2]) + float(state.length)},
            };

            figure_state.connections = {
                {0,1},
                {1,2},
                {2,0},

                {0,3},
                {1,3},
                {2,3},
            };

            for(auto &p: figure_state.points) {
                figure_state.c.x += p.x;
                figure_state.c.y += p.y;
                figure_state.c.z += p.z;
            }

            figure_state.c.x /= figure_state.points.size();
            figure_state.c.y /= figure_state.points.size();
            figure_state.c.z /= figure_state.points.size();
            return figure_state;
        
        default:
            return figure_state;
    }
}
