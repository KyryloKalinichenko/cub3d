#include <stdio.h>

int main(void)
{
	int i;

	i = 7;
	printf("%5d\n", (i & 2) >> 1);
}
