#include "cub_head.h"
/*
void    ray_fun(t_data *mlx_s)
{
    double ra;
    int     dof;
    double aTan;
    int i;
    int mx;
    int mp;
    int my;
    int py = mlx_s->player.x / (mlx_s->map_s->width / 2);
    int px = mlx_s->player.y / (mlx_s->map_s->height / 2);

    i = 0;
    ra = mlx_s->player.a;
    printf("%f ", ra);
    while(i++ < 1)
    {  
        dof = 0;
        aTan = -1 / tan(ra);
        if (ra > PI)
        {
            mlx_s->ray_s.ry = (((int)py > 6) << 6) - 0.0001;
            mlx_s->ray_s.rx = (py - mlx_s->ray_s.ry) * aTan + px;
            mlx_s->ray_s.yo = -64;
            mlx_s->ray_s.xo = -mlx_s->ray_s.yo * aTan;
        }
        if (ra < PI)
        {
            mlx_s->ray_s.ry = (((int)py > 6) << 6) + 64;
            mlx_s->ray_s.rx = (py - mlx_s->ray_s.ry) * aTan + px;
            mlx_s->ray_s.yo = 64;
            mlx_s->ray_s.xo = -mlx_s->ray_s.yo * aTan;
        }
        if (ra == 0 || ra == PI)
        {
            mlx_s->ray_s.rx = mlx_s->player.x;
            mlx_s->ray_s.ry = mlx_s->player.y;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = ((int)(mlx_s->ray_s.rx)) > 6;
            my = ((int)(mlx_s->ray_s.ry)) > 6;
            mp = my * mlx_s->map_s->mapX + mx;
            printf("%i %i", mx, my);
            if (mp < mlx_s->map_s->mapX * mlx_s->map_s->mapY && mlx_s->map_s->map[mx][my] == '1')
                dof = 8;
            else
                {
                    mlx_s->ray_s.rx += mlx_s->ray_s.xo;
                    mlx_s->ray_s.ry += mlx_s->ray_s.yo;
                    dof += 1;
                }
        }
        t_line vector;

        vector.x = px;
        vector.y = py;
        vector.dx = mlx_s->ray_s.rx;
        vector.dy = mlx_s->ray_s.ry;
        print_v(mlx_s, vector);
    }
}*/

static void	first_step(t_ray *ray)
{
	if (ray->ray_dir->x < 0)
	{
		ray->step->x = -1;
		ray->side_dist->x =
					(ray->pos->x - ray->on_map->x) * ray->delta_dist->x;
	}
	else
	{
		ray->step->x = 1;
		ray->side_dist->x =
					(ray->on_map->x + 1 - ray->pos->x) * ray->delta_dist->x;
	}
	if (ray->ray_dir->y < 0)
	{
		ray->step->y = -1;
		ray->side_dist->y =
				(ray->pos->y - ray->on_map->y) * ray->delta_dist->y;
	}
	else
	{
		ray->step->y = 1;
		ray->side_dist->y =
				(ray->on_map->y + 1 - ray->pos->y) * ray->delta_dist->y;
	}
}

void	dda(t_ray *ray, t_data *mlx_s)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist->x < ray->side_dist->y)
		{
			ray->side_dist->x += ray->delta_dist->x;
			ray->on_map->x += ray->step->x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist->y += ray->delta_dist->y;
			ray->on_map->y += ray->step->y;
			ray->side = 1;
		}
		if (mlx_s->map_s->map[(int)(ray->on_map->x)][(int)(ray->on_map->y)] == '1')
			ray->hit = 1;
        if (ray->hit == 1)
        {
           /* t_line vector;
            vector.x = mlx_s->player.x;
	        vector.y = mlx_s->player.y; 
	        vector.dx = ;
	        vector.dy = vector.y + (mlx_s->player.dy * 20);
	        print_v(mlx_s, vector);*/
            printf("size of sq = (height) %i * (width) %i \n ", mlx_s->map_s->height, mlx_s->map_s->width);
            printf("step  x -------> %f\n step  y -------> %f\n ", ray->step->x, ray->step->y);
            printf("boom  x -------> %f\n boom  y -------> %f\n ", ray->on_map->x, ray->on_map->y);
        }
		//if (BONUS == 1)
		//	if (mlx_s->map[(int)(ray->on_map->x)][(int)(ray->on_map->y)] == '4')
		//		ray->hit = 1;
	}
}

void    init_ray(t_ray  *ray, t_data *mlx_s)
{
    ray->ray_dir = malloc(sizeof(t_point));
    ray->dir = malloc(sizeof(t_point));
    ray->direction = malloc(sizeof(t_point));
    ray->on_map = malloc(sizeof(t_point));
    ray->step = malloc(sizeof(t_point));
    ray->side_dist = malloc(sizeof(t_point));
    ray->delta_dist = malloc(sizeof(t_point));
    ray->plane = malloc(sizeof(t_point));
    ray->pos = malloc(sizeof(t_point));


    ray->pos->x = mlx_s->player.x;
    ray->pos->y = mlx_s->player.y;
    ray->dir->x = PI / 4;
    ray->dir->y = 0;
    ray->plane->x = 0;
    ray->plane->y = 0.66;
}

void    ray_fun(t_data *mlx_s)
{
    t_ray   *ray = malloc(sizeof(t_ray));
    int     i;

    i = -1;
    init_ray(ray, mlx_s);
    while (++i < mlx_s->player.x)
    {
        ray->camera_x = 2 * i / ray->pos->x - 1;
	    ray->ray_dir->x = ray->dir->x + ray->plane->x * ray->camera_x;
	    ray->ray_dir->y = ray->dir->y + ray->plane->y * ray->camera_x;
	    ray->on_map->x = (int)(ray->pos->x / mlx_s->map_s->width);
	    ray->on_map->y = (int)(ray->pos->y / mlx_s->map_s->height);
	    ray->delta_dist->x = fabs(1 / ray->ray_dir->x);
	    ray->delta_dist->y = fabs(1 / ray->ray_dir->y);
	    ray->hit = 0;
        first_step(ray);
        //printf(" --------%f----------> \n", ray->side_dist->x);
        dda(ray, mlx_s);
    }
}