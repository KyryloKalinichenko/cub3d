#include "cub_head.h"

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
					(ray->on_map->x + 1.0 - ray->pos->x) * ray->delta_dist->x;
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
				(ray->on_map->y + 1.0 - ray->pos->y) * ray->delta_dist->y;
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
		if (mlx_s->map_s->map[(int)(ray->on_map->y)][(int)(ray->on_map->x)] == '1')
			ray->hit = 1;
        if (ray->hit == 1)
        {/*
            printf("----------------------------------------------------------\n");
            printf("ray_pos  x -------> %f\n ray_pos  y -------> %f\n ", ray->pos->x, ray->pos->y);
            printf("----------------------------------------------------------\n");
            printf("map  x -------> %f\n map  y -------> %f\n ", ray->on_map->x, ray->on_map->y);
            printf("----------------------------------------------------------\n");
            printf("size of sq = (height) %i * (width) %i \n ", mlx_s->map_s->height, mlx_s->map_s->width);
            printf("----------------------------------------------------------\n");*/
            //printf("step  x -------> %f\n step  y -------> %f\n ", ray->step->x, ray->step->y);
            //printf("----------------------------------------------------------\n");
            //printf("delta_dist  x -------> %f\n boom  y -------> %f\n ", ray->delta_dist->x, ray->delta_dist->y);
            //printf("----------------------------------------------------------\n");
            //printf("side_dist  x -------> %f\n boom  y -------> %f\n ", ray->side_dist->x, ray->side_dist->y);
            //printf("/////////////////////////////////////////////////////////////\n");
            
        }
	}
}

void    turn_l(t_ray *ray)
{
/*    double	old_dir_x;
	double	old_plane_x;

	old_dir_x = ray->dir->x;
	old_plane_x = ray->plane->x;
	ray->dir->x = old_dir_x * cos(SPEED)
					- ray->dir->y * sin(SPEED);
	ray->dir->y = old_dir_x * sin(SPEED)
					+ ray->dir->y * cos(SPEED);
	ray->plane->x = old_plane_x * cos(SPEED)
					- ray->plane->y * sin(SPEED);
	ray->plane->y = old_plane_x * sin(SPEED)
					+ ray->plane->y * cos(SPEED);
*/
	double oldDirX = ray->dir->x;
    double oldPlaneX = ray->plane->x;
    ray->dir->x = ray->dir->x * cos(-SPEED) - ray->dir->y * sin(-SPEED);
    ray->dir->y = oldDirX * sin(-SPEED) + ray->dir->y * cos(-SPEED);
    ray->plane->x = ray->plane->x * cos(-SPEED) - ray->plane->y * sin(-SPEED);
    ray->plane->y = oldPlaneX * sin(-SPEED) + ray->plane->y * cos(-SPEED);
    
}

void    turn_r(t_ray *ray)
{/*
    double	old_dir_x;
	double	old_plane_x;

	old_dir_x = ray->dir->x;
	old_plane_x = ray->plane->x;
	ray->dir->x = old_dir_x * cos(-SPEED)
					- ray->dir->y * sin(-SPEED);
	ray->dir->y = old_dir_x * sin(-SPEED)
					+ ray->dir->y * cos(-SPEED);
	ray->plane->x = old_plane_x * cos(-SPEED)
					- ray->plane->y * sin(-SPEED);
	ray->plane->y = old_plane_x * sin(-SPEED)
					+ ray->plane->y * cos(-SPEED);*/
	double oldDirX = ray->dir->x;
    double oldPlaneX = ray->plane->x;
    ray->dir->x = ray->dir->x * cos(SPEED) - ray->dir->y * sin(SPEED);
    ray->dir->y = oldDirX * sin(SPEED) + ray->dir->y * cos(SPEED);
    ray->plane->x = ray->plane->x * cos(SPEED) - ray->plane->y * sin(SPEED);
    ray->plane->y = oldPlaneX * sin(SPEED) + ray->plane->y * cos(SPEED);
}

void    init_ray(t_ray  *ray/*, t_data *mlx_s*/)
{
    ray->ray_dir = malloc(sizeof(t_point));
    ray->dir = malloc(sizeof(t_point));
    ray->on_map = malloc(sizeof(t_on_map));
    ray->step = malloc(sizeof(t_on_map));
    ray->side_dist = malloc(sizeof(t_point));
    ray->delta_dist = malloc(sizeof(t_point));
    ray->plane = malloc(sizeof(t_point));
    ray->pos = malloc(sizeof(t_point));

    //ray->pos->x = /*((mlx_s->player.x + (mlx_s->map_s->width / 2))*/mlx_s->player.x / mlx_s->map_s->width;
    //ray->pos->y = /*((mlx_s->player.y + (mlx_s->map_s->height / 2))*/mlx_s->player.y / mlx_s->map_s->height;
	ray->pos->x = 2;
	ray->pos->y = 2;
	ray->dir->x = -1;
    ray->dir->y = 0;
    ray->plane->x = 0;
    ray->plane->y = 0.66;
}

void	main_image(t_data *mlx_s, t_ray *ray, int i)
{
		double perpWallDist;
        double lineHeight;
        int drawEnd;
        
		if (ray->side == 0) 
            perpWallDist = (ray->on_map->x - ray->pos->x + (1 - ray->step->x) / 2) / ray->ray_dir->x;
        else           
            perpWallDist = (ray->on_map->y - ray->pos->y + (1 - ray->step->y) / 2) / ray->ray_dir->y;
        lineHeight = (int)(mlx_s->height / perpWallDist);
        int drawStart = -lineHeight / 2 + mlx_s->height / 2;
        if(drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + mlx_s->height / 2;
        if(drawEnd >= mlx_s->height)
            drawEnd = mlx_s->height - 1;
		put_text(drawStart, drawEnd, i, mlx_s, lineHeight, perpWallDist);
		//print_ver_line(drawStart, drawEnd, i, mlx_s);	
}

void    ray_fun(t_data *mlx_s, t_ray *ray)
{
    int     i;
	//t_line vector;

    i = -1;
    while (++i < mlx_s->width)
    {
		print_back(0, mlx_s->height, i, mlx_s);
        ray->camera_x = 2 * i / (double)(mlx_s->width) - 1;
	    ray->ray_dir->x = ray->dir->x + ray->plane->x * ray->camera_x;
	    ray->ray_dir->y = ray->dir->y + ray->plane->y * ray->camera_x;
	    ray->on_map->x = (int)(ray->pos->x);
	    ray->on_map->y = (int)(ray->pos->y);
	    ray->delta_dist->x = fabs(1 / ray->ray_dir->x);
	    ray->delta_dist->y = fabs(1 / ray->ray_dir->y);
        ray->hit = 0;
        first_step(ray);
        dda(ray, mlx_s);
		main_image(mlx_s, ray, i);
		/*vector.x = mlx_s->ray->pos->x * mlx_s->map_s->width;
		vector.y = mlx_s->ray->pos->y * mlx_s->map_s->height; 
		vector.dx = mlx_s->ray->on_map->x * mlx_s->map_s->width;
		vector.dy = mlx_s->ray->on_map->y * mlx_s->map_s->height;
		print_v(mlx_s, vector);*/
    }
}