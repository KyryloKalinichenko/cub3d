#include "cub_head.h"

void    ray_fun(t_data *mlx_s)
{
    double ra;
    int     dof;
    double aTan;
    int i;
    int py = mlx_s->player.x / (mlx_s->map_s->width / 2);
    int px = mlx_s->player.y / (mlx_s->map_s->height / 2);

    i = 0;
    ra = mlx_s->player->a;
    while(i++ < 1)
    {  
        dof = 0;
        aTan = -1 / tan(ra);
        if (ra > PI)
        {
            mlx_s->ray_s.ry = (((int)py>>6)<<6) - 0.0001;
            mlx_s->ray_s.rx = (py - mlx_s->ray_s.ry) * aTan + px;
            mlx_s->ray_s.yo = -64;
        }

    }
}