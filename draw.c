#include "cub_head.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

static void print_line(t_data *mlx_s, int x, int y)
{
    int goal_x;

    goal_x = x + mlx_s->map_s->height;
    while(x <= goal_x && x < mlx_s->width)
    {
        my_mlx_pixel_put(mlx_s, x, y, mlx_s->map_s->color);
        x++;
    }

}

void            print_sq(t_data *mlx_s, int x, int y)
{
    int goal_y;

    goal_y = y + mlx_s->map_s->height;
    while(y <= goal_y && y < mlx_s->height)
    {
        print_line(mlx_s, x, y);
        y++;
    }
}

 void            print_string(t_data *mlx_s, char *s, int y)
{
    int x;

    x = 0;
    while(s && *s != '\n' && x < mlx_s->width)
    {
        if (*s == '1')
        {
            mlx_s->map_s->color = 0x00FF0000;
            print_sq(mlx_s, x, y);
        }
        else
        {
            mlx_s->map_s->color = 0x000000FF;
            print_sq(mlx_s, x, y);
        }
        s++;
        x += mlx_s->map_s->width;
    }
}

void            print_map(t_data *mlx_s)
{
    int i;
    int y;

    i = 0;
    y = 0;
    while(mlx_s->map_s->map[i] && y < mlx_s->height)
    {
        printf("%s\n", mlx_s->map_s->map[i]);
        print_string(mlx_s, mlx_s->map_s->map[i++], y);
      // mlx_s->map_s->color = 0x00FF0000;
        //print_sq(mlx_s, 100, 100);
        y += mlx_s->map_s->height;
    }
    //print_sq(mlx_s, 0, 0);
    //printf("%d\n", mlx_s->map_s->height);
    //printf("%d\n", mlx_s->map_s->width);
}