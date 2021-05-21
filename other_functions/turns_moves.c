/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:19:28 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/08 18:26:07 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

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

/*
** Two following functions performs players movements
** and ensures that there is no wall on the way. 
**
*/

void	back_forth(t_data *mlx_s, int keycode)
{
	if (keycode == FORTH)
	{
		if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->y + mlx_s->ray->dir->y
				* (MSPEED + 0.1))][(int)(mlx_s->ray->pos->x)] == '0')
			mlx_s->ray->pos->y += mlx_s->ray->dir->y * MSPEED;
		if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->y)][(int)
			(mlx_s->ray->pos->x + mlx_s->ray->dir->x * (MSPEED + 0.1))] == '0')
			mlx_s->ray->pos->x += mlx_s->ray->dir->x * MSPEED;
	}
	if (keycode == BACK)
	{
		if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->y - mlx_s->ray->dir->y
				* (MSPEED + 0.1))][(int)(mlx_s->ray->pos->x)] == '0')
			mlx_s->ray->pos->y -= mlx_s->ray->dir->y * MSPEED;
		if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->y)][(int)
			(mlx_s->ray->pos->x - mlx_s->ray->dir->x * (MSPEED + 0.1))] == '0')
			mlx_s->ray->pos->x -= mlx_s->ray->dir->x * MSPEED;
	}
}

void	left_right(t_data *mlx_s, int keycode, char **map)
{
	double	r_p_x;
	double	r_p_y;
	double	r_d_x;
	double	r_d_y;

	r_d_x = mlx_s->ray->dir->x;
	r_d_y = mlx_s->ray->dir->y;
	r_p_x = mlx_s->ray->pos->x;
	r_p_y = mlx_s->ray->pos->y;
	if (keycode == LEFT)
	{
		if (map[(int)(r_p_y + r_d_x * (MSPEED + 0.1))][(int)(r_p_x)] == '0')
			mlx_s->ray->pos->y += r_d_x * MSPEED;
		if (map[(int)(r_p_y)]
				[(int)(r_p_x - r_d_y * (MSPEED + 0.1))] == '0')
			mlx_s->ray->pos->x -= r_d_y * MSPEED;
	}
	if (keycode == RIGHT)
	{
		if (map[(int)(r_p_y - r_d_x * (MSPEED + 0.1))]
			[(int)(r_p_x)] == '0')
			mlx_s->ray->pos->y -= r_d_x * MSPEED;
		if (map[(int)(r_p_y)][(int)(r_p_x + r_d_y * (MSPEED + 0.1))] == '0')
			mlx_s->ray->pos->x += r_d_y * MSPEED;
	}
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
	if (!ray->ray_dir || !ray->dir || !ray->on_map
		|| !ray->step || !ray->side_dist || !ray->delta_dist
		|| !ray->plane || !ray->pos)
		error(1);
	load(ray, start);
	turn_start(ray, start->point);
}
