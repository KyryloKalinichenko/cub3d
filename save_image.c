//#include "cub_head.h"
#include <stdio.h>

int    main()
{
    unsigned int m;
    unsigned char i;

    m = 0x00FF00FF;
    printf("%i\n", (i = 0x00000000 | ((m >> 16) & 0xFFFFFFFF)));
    printf("%i\n", (m << 0) | 0x0);
    printf("%i\n", (m << 16));
    printf("%i\n", (m << 24));
}