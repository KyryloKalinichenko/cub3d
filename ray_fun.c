/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:19:34 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/07 16:54:45 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

static void	first_step(t_ray *ray)
{
	if (ray->ray_dir->x < 0)
	{
		ray->step->x = -1;
		ray->side_dist->x
			= (ray->pos->x - ray->on_map->x) * ray->delta_dist->x;
	}
	else
	{
		ray->step->x = 1;
		ray->side_dist->x
			= (ray->on_map->x + 1.0 - ray->pos->x) * ray->delta_dist->x;
	}
	if (ray->ray_dir->y < 0)
	{
		ray->step->y = -1;
		ray->side_dist->y
			= (ray->pos->y - ray->on_map->y) * ray->delta_dist->y;
	}
	else
	{
		ray->step->y = 1;
		ray->side_dist->y
			= (ray->on_map->y + 1.0 - ray->pos->y) * ray->delta_dist->y;
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
		if (mlx_s->map_s->map[(int)(ray->on_map->y)]
				[(int)(ray->on_map->x)] == '1')
			ray->hit = 1;
	}
}

void	turn_l(t_ray *ray)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = ray->dir->x;
	oldPlaneX = ray->plane->x;
	ray->dir->x = ray->dir->x * cos(-SPEED) - ray->dir->y * sin(-SPEED);
	ray->dir->y = oldDirX * sin(-SPEED) + ray->dir->y * cos(-SPEED);
	ray->plane->x = ray->plane->x * cos(-SPEED) - ray->plane->y * sin(-SPEED);
	ray->plane->y = oldPlaneX * sin(-SPEED) + ray->plane->y * cos(-SPEED);
}

void	turn_r(t_ray *ray)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = ray->dir->x;
	oldPlaneX = ray->plane->x;
	ray->dir->x = ray->dir->x * cos(SPEED) - ray->dir->y * sin(SPEED);
	ray->dir->y = oldDirX * sin(SPEED) + ray->dir->y * cos(SPEED);
	ray->plane->x = ray->plane->x * cos(SPEED) - ray->plane->y * sin(SPEED);
	ray->plane->y = oldPlaneX * sin(SPEED) + ray->plane->y * cos(SPEED);
}

void	turn_start(t_ray *ray, char c)
{
	if (c == 'N')
	{
		ray->dir->x = 0;
		ray->dir->y = -1;
		ray->plane->x = -0.66;
		ray->plane->y = 0;
	}
	else if (c == 'S')
	{
		ray->dir->x = 0;
		ray->dir->y = 1;
		ray->plane->x = 0.66;
		ray->plane->y = -0;
	}
	else if (c == 'W')
	{
		ray->dir->x = 1;
		ray->dir->y = 0;
		ray->plane->x = 0;
		ray->plane->y = -0.66;
	}
	else if (c == 'E')
	{
		ray->dir->x = -1;
		ray->dir->y = 0;
		ray->plane->x = 0;
		ray->plane->y = 0.66;
	}
}

static void	load(t_ray *ray, t_point *start)
{
	ray->ray_dir->x = 0;
	ray->ray_dir->y = 0;
	ray->ray_dir->point = 0;
	ray->on_map->x = 0;
	ray->on_map->y = 0;
	ray->step->x = 0;
	ray->step->y = 0;
	ray->side_dist->x = 0;
	ray->side_dist->y = 0;
	ray->side_dist->point = 0;
	ray->delta_dist->x = 0;
	ray->delta_dist->y = 0;
	ray->delta_dist->point = 0;
	ray->pos->x = start->x;
	ray->pos->y = start->y;
	ray->pos->point = 0;
	ray->plane->point = 0;
	ray->dir->point = 0;
}

void	init_ray(t_ray *ray, t_point *start)
{
	ray->ray_dir = malloc(sizeof(t_point));
	ray->dir = malloc(sizeof(t_point));
	ray->on_map = malloc(sizeof(t_on_map));
	ray->step = malloc(sizeof(t_on_map));
	ray->side_dist = malloc(sizeof(t_point));
	ray->delta_dist = malloc(sizeof(t_point));
	ray->plane = malloc(sizeof(t_point));
	ray->pos = malloc(sizeof(t_point));
	/*if (!ray->ray_dir || !ray->dir || !ray->on_map
		|| !ray->step || !ray->side_dist || !ray->delta_dist
		|| !ray->plane || !ray->pos)
		malloc_error();*/
	load(ray, start);
	turn_start(ray, start->point);
}

int	main_image(t_data *mlx_s, t_ray *ray, int i)
{
	t_wall	wall;
	t_tex	*tex;

	tex = NULL;
	if (ray->side == 0)
		wall.perpWallDist = (ray->on_map->x - ray->pos->x
				+ (1 - ray->step->x) / 2) / ray->ray_dir->x;
	else
		wall.perpWallDist = (ray->on_map->y - ray->pos->y
				+ (1 - ray->step->y) / 2) / ray->ray_dir->y;
	//printf("%f\n", wall.perpWallDist);
	wall.lineHeight = (int)(mlx_s->height / wall.perpWallDist);
	wall.drawStart = -wall.lineHeight / 2 + mlx_s->height / 2;
	wall.drawEnd = wall.lineHeight / 2 + mlx_s->height / 2;
	if (wall.drawStart < 0)
		wall.drawStart = 0;
	if (wall.drawEnd >= mlx_s->height)
		wall.drawEnd = mlx_s->height - 1;
	if (ray->on_map->y - ray->pos->y > 0 && ray->side == 1)
		tex = mlx_s->tex->so_side;
	else if (ray->on_map->y - ray->pos->y <= 0 && ray->side == 1)
		tex = mlx_s->tex->no_side;
	else if (ray->on_map->x - ray->pos->x > 0 && ray->side == 0)
		tex = mlx_s->tex->we_side;
	else if (ray->on_map->x - ray->pos->x <= 0 && ray->side == 0)
		tex = mlx_s->tex->ea_side;
	put_text(i, mlx_s, &wall, tex);
	return (wall.perpWallDist);
}

void	ray_fun(t_data *mlx_s, t_ray *ray)
{
	int	i;
	double zbuffer[mlx_s->width];

	i = -1;
	print_floor(mlx_s, ray);
	while (++i < mlx_s->width)
	{
		//print_back(0, mlx_s->height - 1, i, mlx_s)
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
		zbuffer[i] = main_image(mlx_s, ray, i);
	}
	print_sprite(mlx_s, mlx_s->ray, zbuffer);
}
