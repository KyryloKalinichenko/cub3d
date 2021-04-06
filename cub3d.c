#include "cub_head.h"

/*
** The main function for my project. Here the main loop running and all other functions is calling.  
*/

int    move(int keycode, t_data *mlx_s)
{
    //printf("/////%i/////\n", keycode);
    print_map(mlx_s);
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
        mlx_s->player.a -= 0.1;
        if (mlx_s->player.a < 0)
            mlx_s->player.a += 2 * PI;
        mlx_s->player.dx = cos(mlx_s->player.a) * 10;
        mlx_s->player.dy = sin(mlx_s->player.a) * 10;
    }
    if (keycode == RIGHT)
    {
        mlx_s->player.a += 0.1;
        if (mlx_s->player.a > (2 * PI))
            mlx_s->player.a -= 2 * PI;
        mlx_s->player.dx = cos(mlx_s->player.a) * 10;
        mlx_s->player.dy = sin(mlx_s->player.a) * 10;
    }
    printf("boom  x ------->\n");
    mlx_s->ray->dir->x = cos(mlx_s->player.a);
    mlx_s->ray->dir->y = sin(mlx_s->player.a);

    mlx_s->ray->pos->x = (mlx_s->player.x / mlx_s->map_s->width);
    mlx_s->ray->pos->y = (mlx_s->player.y / mlx_s->map_s->height);
    print_player(mlx_s);
    mlx_put_image_to_window(mlx_s->mlx, mlx_s->mlx_win, mlx_s->img, 0, 0);
    
    return(0);
}

int main(int argc, char **argv)
{
    t_data mlx_s;
    //mlx_s = malloc(sizeof(t_data));
    if (argc == 1)
        return(printf("Error\n"));
    init(&mlx_s, argv[1]);
   // printf("-----%i-----", mlx_s.height);
   // mlx_put_image_to_window(mlx_s.mlx, mlx_s.mlx_win, mlx_s.img, 0, 0);
    mlx_hook (mlx_s.mlx_win, 2, 1L<<0, move, &mlx_s);
    //mlx_put_image_to_window(mlx_s.mlx, mlx_s.mlx_win, mlx_s.img, 0, 0);
    mlx_loop(mlx_s.mlx);
}