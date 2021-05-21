/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:33:18 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/08 18:38:13 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

void	turn_start2(t_ray *ray, char c)
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
}

void	turn_start(t_ray *ray, char c)
{
	if (c == 'W')
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
	turn_start2(ray, c);
}

void	load(t_ray *ray, t_point *start)
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
