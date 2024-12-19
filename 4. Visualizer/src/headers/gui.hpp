#include <SDL2/SDL.h>

extern const char* figures[];
extern int select;

void GUI_Init(SDL_Window* window, SDL_Renderer* renderer);
void GUI_Close();
int GUI_Renderer(float my_color[4], float my_rads[3], int* length, int position[2]);