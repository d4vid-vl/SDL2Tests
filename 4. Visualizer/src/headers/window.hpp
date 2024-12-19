#define WINDOW_HEIGHT 1024
#define WINDOW_WIDTH 768
#define FPS 30
#define FRAME_TARGET_TIME (1000/FPS)
#include <vector>
#include "gui.hpp"

// Base constants
struct State {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    std::vector<SDL_FPoint> points;
    float my_color[4] = {1, 1, 1, 1};
    float my_rads[3] = {0.00300, 0.00300, 0.00300};
    int length = 200;
    int position[3] = {200, 200, 200};
    u_int32_t pixels[WINDOW_HEIGHT * WINDOW_WIDTH];
    bool isRunning;
};

struct vec3 {
    double x,y,z;
};

struct connection {
    int a,b;
};

struct figure_state{
    std::vector<vec3> points;
    std::vector<connection> connections;
    vec3 c{0,0,0};
};

extern State state;

void init_window();
void close_window();
void event_processor();
void pixel(float x, float y);
void line(float x1, float y1, float x2, float y2);
void show();
void rotate(vec3 &point, float x = 1, float y = 1, float z = 1);
void clear();
figure_state sel_figure(int figure);