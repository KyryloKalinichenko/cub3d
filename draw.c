#include "cub_head.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void            mlx_pixel_get(t_tex *data, int x, int y, unsigned int *color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *color = *(unsigned int*)dst;
}

void            mlx_pixel_get_2(t_data *data, int x, int y, int *color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *color = *(unsigned int*)dst;
}
/*
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
*/
void    print_back(int drawStart, int drawEnd, int x, t_data *mlx_s)
{
    while(drawStart <= drawEnd / 2)
    {
        my_mlx_pixel_put(mlx_s, x, drawStart, mlx_s->cel);
        drawStart++;
    }
    while(drawStart <= drawEnd)
    {
        my_mlx_pixel_put(mlx_s, x, drawStart, mlx_s->floor);
        drawStart++;
    }
    //printf("%10d%10d\n", mlx_s->cel, mlx_s->floor);
}

static void print_line(t_data *mlx_s, int x, int y, int color)
{
    int goal_x;

    goal_x = x + mlx_s->map_s->width;
    while(x <= goal_x && x < mlx_s->width)
    {
        my_mlx_pixel_put(mlx_s, x, y, color);
        x++;
    }

}

void            print_sq(t_data *mlx_s, int x, int y, int color)
{
    int goal_y;

    goal_y = y + mlx_s->map_s->height;
    while(y <= goal_y && y < mlx_s->height)
    {
        print_line(mlx_s, x, y, color);
        y++;
    }
}

 void            print_string(t_data *mlx_s, char *s, int y)
{
    int x;

    x = 0;
    while(*s)
    {
        if (*s == '1' || *s == '2')
            print_sq(mlx_s, x, y, 0x0FFF0000);
        else
            print_sq(mlx_s, x, y, 0x0F0000FF);
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
        print_string(mlx_s, mlx_s->map_s->map[i++], y);
        y += mlx_s->map_s->height;
    }
}


static void print_celling(t_data *mlx_s, double floorX, double floorY, double floorStepX, double floorStepY, int y)
{
    int cellX;
    int cellY;
    int tx;
    int ty;
    unsigned int color;

      for(int x = 0; x < mlx_s->width; ++x)
      {
        cellX = (int)(floorX);
        cellY = (int)(floorY);
        tx = (int)(64 * (floorX - cellX)) & (64 - 1);
        ty = (int)(64 * (floorY - cellY)) & (64 - 1);
        floorX += floorStepX;
        floorY += floorStepY;
        mlx_pixel_get(mlx_s->tex->no_side, tx, ty, &color);
        my_mlx_pixel_put(mlx_s, x, y, color);
        mlx_pixel_get(mlx_s->tex->ea_side, tx, ty, &color);
        my_mlx_pixel_put(mlx_s, x, (mlx_s->height - y - 1), color);
      }
}

void    print_floor(t_data *mlx_s, t_ray *ray)
{
    float rayDirX0;
    float rayDirY0;
    float rayDirX1;
    float rayDirY1;
    int p;
    float posZ;
    float rowDistance;
    float floorStepX;
    float floorStepY;
    float floorX;
    float floorY;

   for(int y = 0; y < mlx_s->height; y++)
    {
        rayDirX0 = ray->dir->x - ray->plane->x;
        rayDirY0 = ray->dir->y - ray->plane->y;
        rayDirX1 = ray->dir->x + ray->plane->x;
        rayDirY1 = ray->dir->y + ray->plane->y;
        p = y - mlx_s->height / 2;
        posZ = 0.5 * mlx_s->height;
        rowDistance = posZ / p;
        floorStepX = rowDistance * (rayDirX1 - rayDirX0) / mlx_s->width;
        floorStepY = rowDistance * (rayDirY1 - rayDirY0) / mlx_s->width;
        floorX = ray->pos->x + rowDistance * rayDirX0;
        floorY = ray->pos->y + rowDistance * rayDirY0;
        print_celling(mlx_s, floorX, floorY, floorStepX, floorStepY, y);
    } 
}