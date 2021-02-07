#include <SDL2/SDL.h>
#include <assert.h>

SDL_Window* window;
SDL_Renderer* renderer;

const int WIDTH=20;
const bool* b[7]=
{
    

};

void update();
void drawBlock(int x,int y);
void clear();

int main(int argc,char* argv[])
{
    window=SDL_CreateWindow("Tetris",
    SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
    10*WIDTH,20*WIDTH,SDL_WINDOW_SHOWN);
    assert(window);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    assert(renderer);
    

    


    return 0;
}


