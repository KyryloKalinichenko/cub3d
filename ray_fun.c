/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:19:34 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/08 18:14:08 by kkalinic         ###   ########.fr       */
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
	wall.lineHeight = (int)(mlx_s->height / wall.perpWallDist);
	wall.drawStart = -wall.lineHeight / 2 + mlx_s->height / 2;
	wall.drawEnd = wall.lineHeight / 2 + mlx_s->height / 2;
	limits(&wall.drawStart, &wall.drawEnd, mlx_s->height - 1);
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

static void	calc(t_ray *ray, int i, t_data *mlx_s)
{
	ray->camera_x = 2 * i / (double)(mlx_s->width) - 1;
	ray->ray_dir->x = ray->dir->x + ray->plane->x * ray->camera_x;
	ray->ray_dir->y = ray->dir->y + ray->plane->y * ray->camera_x;
	ray->on_map->x = (int)(ray->pos->x);
	ray->on_map->y = (int)(ray->pos->y);
	ray->delta_dist->x = fabs(1 / ray->ray_dir->x);
	ray->delta_dist->y = fabs(1 / ray->ray_dir->y);
	ray->hit = 0;
}

void	ray_fun(t_data *mlx_s, t_ray *ray)
{
	int		i;
	double	*zbuffer;

	i = -1;
	if (!(zbuffer
			= malloc(sizeof(double) * mlx_s->width)))
		malloc_error();
	if (FLOOR)
		print_floor(mlx_s, ray);
	while (++i < mlx_s->width)
	{
		if (!FLOOR)
			print_back(0, mlx_s->height - 1, i, mlx_s);
		calc(ray, i, mlx_s);
		first_step(ray);
		dda(ray, mlx_s);
		zbuffer[i] = main_image(mlx_s, ray, i);
	}
	print_sprite(mlx_s, mlx_s->ray, zbuffer);
}
