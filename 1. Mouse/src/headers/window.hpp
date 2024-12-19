#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 480
#define FPS 30
#define FRAME_TARGET_TIME (1000/FPS)

// Base constants
struct State {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    u_int32_t pixels[WINDOW_HEIGHT * WINDOW_WIDTH];
    int mouse_x;
    int mouse_y;
    bool isRunning;
};

extern State state;

void init_window();
void close_window();
void event_processor();
void render();
