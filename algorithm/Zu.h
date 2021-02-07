#pragma once
#include <stdio.h>
#include <stdlib.h>
/*
一直向右走，右遇障碍、边界时下遇障碍、边界则标记障碍并返回，否则向下走，
向右走、向下走后若到b点cnt++。
若返回时在起点则返回结果。
solve:返回cnt
*/
class Zu
{
public:
    Zu(int bx,int by,int hx,int hy)
    {
        map=(bool*)calloc(((size_x=bx)+1)*((size_y=by)+1),sizeof(bool));
        set(hx,hy);
        set(hx-2,hy-1);
        set(hx-2,hy+1);
        set(hx+2,hy-1);
        set(hx+2,hy+1);
        set(hx-1,hy-2);
        set(hx-1,hy+2);
        set(hx+1,hy-2);
        set(hx+1,hy+2);
    }
    ~Zu()
    {
        free(map);
    }
    const int& solve()
    {
        while (!(x==0&&y==0&&get(1,0)&&get(0,1)))
        {
            if (!get(x+1,y))
            {
                old_x=x++;
                if (x==size_x-1&&y==size_y-1)
                    ++cnt;
            }
            else if (!get(x,y+1))
            {
                old_y=y++;
                if (x==size_x-1&&y==size_y-1)
                    ++cnt;
            }
            else
            {
                set(x,y);
                x=old_x;
                y=old_y;
            }
        }
        return cnt;
    }
private:
    bool* map;
    int size_x,size_y;
    int x=0,y=0;
    int old_x=0,old_y=0;
    int cnt=0;
    bool get(const int& x,const int& y)
    {
        if (!(x>=0||y>=0||x<size_x||y<size_y)||(map[y*size_x+x]))
            return true;
        else
            return false;
    }
    void set(const int& x,const int& y)
    {
        if (x>=0||y>=0||x<size_x||y<size_y)
            map[y*size_x+x]=true;
    }

};
