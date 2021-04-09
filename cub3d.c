#include "cub_head.h"

/*
** The main function for my project. Here the main loop running and all other functions is calling.  
*/

int    move(int keycode, t_data *mlx_s)
{
    if (keycode == FORTH)
    {
        mlx_s->player.y += mlx_s->player.dy;
        mlx_s->player.x += mlx_s->player.dx;
    }
    if (keycode == BACK)
    {   
        mlx_s->player.y -= mlx_s->player.dy;
        mlx_s->player.x -= mlx_s->player.dx;
    }
    if (keycode == LEFT)
    {
        turn_l(mlx_s->ray);
        mlx_s->player.dx = mlx_s->ray->dir->x * 3;
        mlx_s->player.dy = mlx_s->ray->dir->y * 3;
    }
    if (keycode == RIGHT)
    {
        turn_r(mlx_s->ray);
        mlx_s->player.dx = mlx_s->ray->dir->x * 3;
        mlx_s->player.dy = mlx_s->ray->dir->y * 3;
    }
    if (keycode == ESC)
        just_exit();
    //printf("%i\n", keycode);
    mlx_s->ray->pos->x = ((mlx_s->player.x + (mlx_s->map_s->width / 2)) / mlx_s->map_s->width);
    mlx_s->ray->pos->y = ((mlx_s->player.y + (mlx_s->map_s->height / 2)) / mlx_s->map_s->height);
    print_player(mlx_s);
    mlx_put_image_to_window(mlx_s->mlx, mlx_s->mlx_win, mlx_s->img, 0, 0);
    return(0);
}

int main(int argc, char **argv)
{
    t_data mlx_s;
   
    if (argc == 1)
        return(printf("Error\n"));
    init(&mlx_s, argv[1]);
    mlx_hook (mlx_s.mlx_win, 2, 1L<<0, move, &mlx_s);
    mlx_loop(mlx_s.mlx);
}