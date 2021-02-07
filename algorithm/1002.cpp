#include <stdio.h>
#include <stdlib.h>
#include "Zu.h"
/*
一直向右走，右遇障碍、边界时下遇障碍、边界则标记障碍并返回，否则向下走，
向右走、向下走后若到b点cnt++。
若返回时在起点则返回结果。
solve:返回cnt
*/

int main()
{
    int bx,by,hx,hy;
    scanf("%d%d%d%d",&bx,&by,&hx,&hy);
    Zu z(bx,by,hx,hy);
    printf("%d",z.solve());
    return 0;
}
