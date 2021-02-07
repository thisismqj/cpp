#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <vector>
class Window
{
public:
    Window(const char* title,int width,int height);
    ~Window();
    void clear();
    void paste(const char* filename,SDL_Rect* src,SDL_Rect* dst);
    void update();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> pics;
};
Window::Window(const char* title,int width,int height)
{
    window=SDL_CreateWindow(title,
    SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
    width,height,
    SDL_WINDOW_FULLSCREEN);
    assert(window);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    assert(renderer);
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
}
Window::~Window()
{
    for (auto i:pics)
    {
        SDL_DestroyTexture(i);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Window::paste(const char* filename,SDL_Rect* src,SDL_Rect* dst)
{
    SDL_Surface* img_sur=NULL;
    img_sur=SDL_LoadBMP(filename);
    assert(img_sur);
    SDL_SetColorKey(img_sur,SDL_TRUE,SDL_MapRGB(img_sur->format,0xFF,0xFF,0xFF));
    pics.insert(pics.end(), SDL_CreateTextureFromSurface(renderer,img_sur));
    SDL_FreeSurface(img_sur);
    SDL_RenderCopy(renderer,pics.back(),src,dst);
}
void Window::clear()
{
    SDL_RenderClear(renderer);
}
void Window::update()
{
    SDL_RenderPresent(renderer);
}
SDL_Rect* rect1=new SDL_Rect{0,0,160,120};
int main(int argc,char* argv[])
{
    Window win("Hello",320,240);
    // SDL_Surface* img_sur=NULL;
    // img_sur=SDL_LoadBMP("hello_world.bmp");
    // assert(img_sur);
    // SDL_Texture* t=SDL_CreateTextureFromSurface(win.renderer,img_sur);
    // SDL_FreeSurface(img_sur);
    // assert(t);
    // SDL_RenderCopy(win.renderer,t,NULL,NULL);
    win.paste("hello_world.bmp",NULL,NULL);
    win.paste("left.bmp",NULL,rect1);
    win.update();
    SDL_Delay(10000);
    return 0;
}