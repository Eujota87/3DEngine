#ifndef INIT_AND_DESTROY
#define INIT_AND_DESTROY

int initialize_window(SDL_Window** window, SDL_Renderer** renderer);
void destroy_window(SDL_Window* window, SDL_Renderer* renderer);

#endif