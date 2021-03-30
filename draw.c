#include "cub_head.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void            print_map(t_data *mlx_s)
{
    int i;

    i = 0;
    while(mlx_s->map_s->map[i])
    {
        printf("%s\n",mlx_s->map_s->map[i++]);
    }
}