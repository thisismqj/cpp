#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <string.h>
static const bool data_blocks[]={
    1,1,1,1,//0
    0,1,0,1,1,1,//4
    1,0,0,1,1,1,//10
    0,0,1,1,1,1,//16
    0,1,1,1,1,0,//22
    1,1,0,0,1,1,//28
    1,1,1,1//34
};
static const int data_indexs[]={0,4,10,16,22,28,34};
static const int data_size_x[]={2,3,3,3,3,3,4};
static const int data_size_y[]={2,2,2,2,2,2,1};
static bool end_input=false;
static int input;
static int score;
static int delay=500;
struct Block{
    int index;
    int x;
    int y;
    int rotation;
};
int randIndex();
bool getPixel(const Block& b,const int& x,const int& y);
void drawRect(SDL_Renderer* ren,const int& x,const int& y);
bool getScene(const bool* scene,const int& x,const int& y);
void setScene(bool* scene,const int& x,const int& y,bool val);
void drawBrick(SDL_Renderer* ren,const Block& b);
void drawScene(SDL_Renderer* ren,const bool* scene);
void draw(SDL_Renderer* ren,const Block& b,const bool* scene);
Uint32 endInput(Uint32 interval,void* param){end_input=true;return delay;}
int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    char* title=new char[16];
    sprintf(title,"Tetris,Score:%d",score);
    SDL_Window* win=SDL_CreateWindow(title,
                                     SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                     10*32,20*32,
                                     SDL_WINDOW_SHOWN);
    if (!win) return -1;
    SDL_Renderer* ren=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
    if (!ren) return -1;
    srand(time(NULL));
    SDL_TimerID timer=SDL_AddTimer(delay,endInput,NULL);
    bool fast=false;
    bool* scene = new bool[10*20];
    memset(scene,0,10*20);
    int sz_x,sz_y;
    Block current;
    Block nw;
    bool wall,bottom;
    SDL_Event e;
s:  current=Block{randIndex(),4,0,3};
    draw(ren,current,scene);
i:  end_input=false;
    input=0;
    while (!end_input)
        while (SDL_PollEvent(&e))
            switch (e.type){
            case SDL_QUIT:
                goto e;
                break;
            case SDL_KEYDOWN:
                input=e.key.keysym.sym;
                nw=current;
                switch (input){
                case SDLK_LEFT:
                    --nw.x;
                    break;
                case SDLK_RIGHT:
                    ++nw.x;
                    break;
                case SDLK_UP:
                    nw.rotation=(nw.rotation+1)%4;
                    break;
                case SDLK_DOWN:
                    delay=10;
                    fast=true;
                    break;
                default:
                    break;
                }
                switch (nw.rotation){
                case 0:case 2:
                    sz_x=data_size_x[nw.index];
                    sz_y=data_size_y[nw.index];
                    break;
                case 1:case 3:
                    sz_x=data_size_y[nw.index];
                    sz_y=data_size_x[nw.index];
                }
                wall=false;
                for (int x=0;x<sz_x;++x)
                    for (int y=0;y<sz_y;++y)
                        if (getPixel(nw,x,y)){
                            if (nw.x+x<0||nw.x+x>=10||nw.y+y>=20) wall=true;
                            if (getScene(scene,nw.x+x,nw.y+y)) wall=true;
                        }
                if (!wall){
                    current=nw;
                    draw(ren,current,scene);
                }
                break;
            }
    switch (current.rotation){
    case 0:case 2:
        sz_x=data_size_x[current.index];
        sz_y=data_size_y[current.index];
        break;
    case 1:case 3:
        sz_x=data_size_y[current.index];
        sz_y=data_size_x[current.index];
    }
    bottom=false;
    for (int x=0;x<sz_x;++x)
        for (int y=0;y<sz_y;++y)
            if (getPixel(current,x,y)){
                if (current.y+y>=19){bottom=true;goto b;}
                if (getScene(scene,current.x+x,current.y+y+1)){bottom=true;goto b;}
            }
b:  if (bottom){
        if (fast){
            fast=false;
            delay=500;
        }
        for (int x=0;x<sz_x;++x)
            for (int y=0;y<sz_y;++y)
                if (getPixel(current,x,y)){
                    if (current.y==0) goto e;
                    setScene(scene,current.x+x,current.y+y,true);
                }
        draw(ren,current,scene);
        bool exist_flag;
        bool full_flag;
        for (int y=19;y>=0;--y){
            exist_flag=false;
            full_flag=true;
            for (int x=0;x<10;++x){
                if (getScene(scene,x,y)) exist_flag=true;
                if (!getScene(scene,x,y)) full_flag=false;
            }
            if (!exist_flag) break;
            if (full_flag){
                ++score;
                sprintf(title,"Tetris,Score:%d",score);
                SDL_SetWindowTitle(win,title);
                for (int ey=y;ey>0;--ey)
                    for (int ex=0;ex<10;++ex)
                        setScene(scene,ex,ey,getScene(scene,ex,ey-1));
                for (int ex=0;ex<10;++ex)
                    setScene(scene,ex,0,false);
                draw(ren,current,scene);
            }
        }
        goto s;

    }else {
        ++current.y;
        draw(ren,current,scene);
        goto i;
    }
e:  delete scene;
    SDL_RemoveTimer(timer);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
int randIndex(){
    return rand()%7;
}
bool getPixel(const Block& b,const int& x,const int& y){
    auto& data=data_blocks;
    const int& d=b.rotation;
    const int& index=data_indexs[b.index];
    const int sz_x=data_size_x[b.index];
    const int sz_y=data_size_y[b.index];
    switch (d){
    case 0:
        return data[index+y*sz_x+x];
    case 1:
        return data[index+(sz_y-1-x)*sz_x+y];
    case 2:
        return data[index+(sz_x-1-x)+(sz_y-1-y)*sz_x];
    case 3:
        return data[index+sz_x*x+(sz_x-1-y)];
    }
}
void drawRect(SDL_Renderer* ren,const int& x,const int& y){
    SDL_Rect r{32*x,32*y,32,32};
    SDL_SetRenderDrawColor(ren,0,255,0,255);
    SDL_RenderFillRect(ren,&r);
}
bool getScene(const bool* scene,const int& x,const int& y){
    return scene[y*10+x];
}
void setScene(bool* scene,const int& x,const int& y,bool val){
    scene[y*10+x]=val;
}
void drawBrick(SDL_Renderer* ren,const Block& b){
    int sz_x,sz_y;
    switch (b.rotation){
    case 0:case 2:
        sz_x=data_size_x[b.index];
        sz_y=data_size_y[b.index];
        break;
    case 1:case 3:
        sz_x=data_size_y[b.index];
        sz_y=data_size_x[b.index];
    }
    for (int x=0;x<sz_x;++x)
        for (int y=0;y<sz_y;++y)
            if (getPixel(b,x,y))
                drawRect(ren,b.x+x,b.y+y);
}
void drawScene(SDL_Renderer* ren,const bool* scene){
    for (int x=0;x<10;++x)
        for (int y=0;y<20;++y)
            if (getScene(scene,x,y))
                drawRect(ren,x,y);
}
void draw(SDL_Renderer* ren,const Block& b,const bool* scene){
    SDL_SetRenderDrawColor(ren,0,0,0,255);
    SDL_RenderClear(ren);
    drawScene(ren,scene);
    drawBrick(ren,b);
    SDL_RenderPresent(ren);
}
