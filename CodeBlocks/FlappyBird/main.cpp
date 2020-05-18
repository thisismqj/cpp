#include <SDL.h>
#include <SDL_hints.h>
#include <iostream>


int main( int argc, char* args[] )
{
    // init
    bool run = true;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* bg = SDL_LoadBMP("bg.bmp");
    if (!bg)return -1;
    SDL_Texture* tx = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
        window = SDL_CreateWindow("SDL_TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  640, 480,
                                  SDL_WINDOW_SHOWN);
        if (window != 0)
        {
            renderer = SDL_CreateRenderer(window, -1, 0);
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);

    SDL_RenderDrawLine(renderer, 25, 25, 78, 78);
    SDL_Rect* rect = new SDL_Rect{15, 28, 155, 128};
    SDL_RenderDrawRect(renderer, rect);
    tx = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_RenderCopy(renderer, tx, NULL, NULL);
    SDL_RenderPresent(renderer);


    SDL_Delay(2000);

    SDL_RenderClear(renderer);
    SDL_DestroyTexture(tx);
    SDL_FreeSurface(bg);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);



    SDL_Quit();
    return 0;
}

