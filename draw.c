/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:15:57 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/04 12:57:06 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

void	print_back(int drawStart, int drawEnd, int x, t_data *mlx_s)
{
	while (drawStart <= drawEnd / 2)
	{
		my_mlx_pixel_put(mlx_s, x, drawStart, mlx_s->cel);
		drawStart++;
	}
	while (drawStart <= drawEnd)
	{
		my_mlx_pixel_put(mlx_s, x, drawStart, mlx_s->floor);
		drawStart++;
	}
}

/*
**static void print_line(t_data *mlx_s, int x, int y, int color)
**{
**    int goal_x;
**
**    goal_x = x + mlx_s->map_s->width;
**    while(x <= goal_x && x < mlx_s->width)
**   {
**        my_mlx_pixel_put(mlx_s, x, y, color);
**        x++;
**    }
**
**}
**
**void            print_sq(t_data *mlx_s, int x, int y, int color)
**{
**    int goal_y;
**
**    goal_y = y + mlx_s->map_s->height;
**    while(y <= goal_y && y < mlx_s->height)
**    {
**        print_line(mlx_s, x, y, color);
**        y++;
**    }
**}
**
** void            print_string(t_data *mlx_s, char *s, int y)
**{
**    int x;
**
**    x = 0;
**    while(*s)
**    {
**        if (*s == '1' || *s == '2')
**            print_sq(mlx_s, x, y, 0x0FFF0000);
**        else
**            print_sq(mlx_s, x, y, 0x0F0000FF);
**        s++;
**        x += mlx_s->map_s->width;
**    }
**}
**
**void            print_map(t_data *mlx_s)
**{
**    int i;
**    int y;
**
**    i = 0;
**    y = 0;
**    while(mlx_s->map_s->map[i])
**    {
**        print_string(mlx_s, mlx_s->map_s->map[i++], y);
**        y += mlx_s->map_s->height;
**   }
**}
*/

/*
** Following two functions are texturise my floor and celling.
**
**
*/

static void	print_ceiling(t_data *mlx_s, t_floor *floor_s)
{
	t_cel			cel_s;
	unsigned int	color;

	cel_s.x = -1;
	while (++cel_s.x < mlx_s->width)
	{
		cel_s.cellX = (int)(floor_s->floorX);
		cel_s.cellY = (int)(floor_s->floorY);
		cel_s.tx = (int)(64 * (floor_s->floorX - cel_s.cellX)) & (64 - 1);
		cel_s.ty = (int)(64 * (floor_s->floorY - cel_s.cellY)) & (64 - 1);
		floor_s->floorX += floor_s->floorStepX;
		floor_s->floorY += floor_s->floorStepY;
		mlx_pixel_get(mlx_s->tex->no_side, cel_s.tx, cel_s.ty, &color);
		color = (color >> 1) & 8355711;
		my_mlx_pixel_put(mlx_s, cel_s.x, floor_s->y, color);
		mlx_pixel_get(mlx_s->tex->ea_side, cel_s.tx, cel_s.ty, &color);
		color = (color >> 1) & 8355711;
		my_mlx_pixel_put(mlx_s, cel_s.x,
			(mlx_s->height - floor_s->y - 1), color);
	}
}

void	print_floor(t_data *mlx_s, t_ray *ray)
{
	t_r_dir	dir_s;
	t_floor	floor_s;

	floor_s.y = -1;
	while (++floor_s.y < mlx_s->height)
	{
		dir_s.rayDirX0 = ray->dir->x - ray->plane->x;
		dir_s.rayDirY0 = ray->dir->y - ray->plane->y;
		dir_s.rayDirX1 = ray->dir->x + ray->plane->x;
		dir_s.rayDirY1 = ray->dir->y + ray->plane->y;
		dir_s.p = floor_s.y - mlx_s->height / 2;
		dir_s.posZ = 0.5 * mlx_s->height;
		dir_s.rowDistance = dir_s.posZ / dir_s.p;
		floor_s.floorStepX = dir_s.rowDistance
			* (dir_s.rayDirX1 - dir_s.rayDirX0) / mlx_s->width;
		floor_s.floorStepY = dir_s.rowDistance
			* (dir_s.rayDirY1 - dir_s.rayDirY0) / mlx_s->width;
		floor_s.floorX = ray->pos->x + dir_s.rowDistance * dir_s.rayDirX0;
		floor_s.floorY = ray->pos->y + dir_s.rowDistance * dir_s.rayDirY0;
		print_ceiling(mlx_s, &floor_s);
	}
}
