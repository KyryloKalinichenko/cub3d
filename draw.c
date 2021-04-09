#include "cub_head.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    print_ver_line(int drawStart, int drawEnd, int x, t_data *mlx_s)
{
    while(drawStart <= drawEnd)
    {
        if (mlx_s->ray->side == 0)
            my_mlx_pixel_put(mlx_s, x, drawStart, 0x00F0F000);
        else
            my_mlx_pixel_put(mlx_s, x, drawStart, (0x00F0F000 / 2));
        drawStart++;
    }
}

void    print_back(int drawStart, int drawEnd, int x, t_data *mlx_s)
{
    while(drawStart <= drawEnd)
    {
        my_mlx_pixel_put(mlx_s, x, drawStart, 0x00000000);
        drawStart++;
    }
}

static void print_line(t_data *mlx_s, int x, int y)
{
    int goal_x;

    goal_x = x + mlx_s->map_s->width;
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
    while(*s)
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
    while(mlx_s->map_s->map[i])
    {
        //printf("%s\n", mlx_s->map_s->map[i]);
        print_string(mlx_s, mlx_s->map_s->map[i++], y);
      // mlx_s->map_s->color = 0x00FF0000;
        //print_sq(mlx_s, 100, 100);
        y += mlx_s->map_s->height;
    }
    //printf("height %i\n", i);
    //printf("%d\n", mlx_s->map_s->height);
    //printf("%d\n", mlx_s->map_s->width);
}