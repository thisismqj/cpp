#include <SDL2\SDL.h>
#include <stdio.h>

SDL_Window* window;
SDL_Surface* surface;
SDL_Surface* left;
SDL_Surface* left_low;
SDL_Surface* right;
SDL_Surface* down;
SDL_Surface* up;
SDL_Surface* start;
// SDL_Rect screen_rect{0,0,320,240};

int main(int argc, char* argv[])
{
	window=SDL_CreateWindow("Key",
	SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
	320,240,
	SDL_WINDOW_SHOWN);
	surface=SDL_GetWindowSurface(window);
	start=SDL_ConvertSurface(SDL_LoadBMP("hello_world.bmp"),surface->format,0);
	left=SDL_ConvertSurface(SDL_LoadBMP("left.bmp"),surface->format,0);
	left_low=SDL_ConvertSurface(SDL_LoadBMP("left_low.bmp"),surface->format,0);
	right=SDL_ConvertSurface(SDL_LoadBMP("right.bmp"),surface->format,0);
	up=SDL_ConvertSurface(SDL_LoadBMP("up.bmp"),surface->format,0);
	down=SDL_ConvertSurface(SDL_LoadBMP("down.bmp"),surface->format,0);
	if (SDL_Init(SDL_INIT_VIDEO)<0||
	window==nullptr||
	start==nullptr||
	left==nullptr||
	right==nullptr||
	up==nullptr||
	down==nullptr)
		printf("%s", SDL_GetError());
	else
	{
		// main
		SDL_Surface* current;
		SDL_Event(e);
		bool q=true;
		SDL_BlitSurface(start,NULL,surface,NULL);
		SDL_UpdateWindowSurface(window);
		while (q)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type==SDL_QUIT)
					q=false;
				else if(e.type==SDL_KEYDOWN)
				{
					switch(e.key.keysym.sym)
					{
						case SDLK_UP:
							current=up;
						break;
						case SDLK_DOWN:
							current=down;
						break;
						case SDLK_LEFT:
							current=left_low;
						break;
						case SDLK_RIGHT:
							current=right;
						break;
						default:
							current=start;
						break;
					}
				}
			}
			SDL_BlitScaled(current,NULL,surface,NULL);
			SDL_UpdateWindowSurface(window);
		}
	}
	SDL_FreeSurface(start);
	SDL_FreeSurface(left);
	SDL_FreeSurface(right);
	SDL_FreeSurface(up);
	SDL_FreeSurface(down);
	start=nullptr;
	left=nullptr;
	right=nullptr;
	up=nullptr;
	down=nullptr;
	SDL_DestroyWindow(window);
	window=nullptr;
	SDL_Quit();
	return 0;
}