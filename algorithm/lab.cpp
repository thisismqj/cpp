#include <stdio.h>

int main()
{
    short c = 1;
    float f = *(float*)&c;
    printf("%d", f);
    return 0;
}