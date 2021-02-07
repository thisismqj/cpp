#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <assert.h>

SDL_Window* window;
SDL_Texture* texture;
SDL_Renderer* renderer;
SDL_Rect* viewport=new SDL_Rect{80,60,160,120};
SDL_Rect* rect1=NULL;
//new SDL_Rect{0,0,80,60};
SDL_Rect* rect2=new SDL_Rect{160,0,160,120};

SDL_Texture* loadTexture(const char* path)
{
    SDL_Texture* new_texture=NULL;
    SDL_Surface* loaded_surface=IMG_Load(path);
    assert(loaded_surface);
    new_texture=SDL_CreateTextureFromSurface(renderer,loaded_surface);
    assert(new_texture);
    SDL_FreeSurface(loaded_surface);
    return new_texture;
}

int main(int argc, char* argv[])
{
    window=SDL_CreateWindow("Hi, Texture!",
    SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
    320,240,
    SDL_WINDOW_SHOWN);
    assert(window);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    assert(renderer);
    SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0x00);
    assert(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG);
    texture=loadTexture("hello.png");
    assert(texture);
    bool r=true;
    SDL_Event* e=new SDL_Event;
    SDL_RenderSetViewport(renderer,viewport);
    while (r)
    {
        while (SDL_PollEvent(e))
        {
            if (e->type==SDL_QUIT)
                r=false;
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,texture,NULL,rect1);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    texture=NULL;
    SDL_DestroyRenderer(renderer);
    renderer=NULL;
    SDL_DestroyWindow(window);
    window=NULL;
    IMG_Quit();
    SDL_Quit();
    return 0;
}