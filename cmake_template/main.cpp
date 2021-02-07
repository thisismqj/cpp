#include <stdio.h>
#include <utility>

int main()
{
	int&& i=20;
	++i;
	printf("%d", i);
}