/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:42:20 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/13 16:47:59 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub_head.h"

void	print_line(t_data *mlx_s, int x, int y, int color)
{
	int	goal_x;

	goal_x = x + mlx_s->map_s->width;
	while (x <= goal_x && x < mlx_s->width)
	{
		my_mlx_pixel_put(mlx_s, x, y, color);
		x++;
	}
}

void	print_sq(t_data *mlx_s, int x, int y, int color)
{
	int	goal_y;

	goal_y = y + mlx_s->map_s->height;
	while (y <= goal_y && y < mlx_s->height)
	{
		print_line(mlx_s, x, y, color);
		y++;
	}
}

static void	print_ln(t_data *mlx_s, int x, int y, int color)
{
	int	goal_x;

	goal_x = x + 5;
	while (x <= goal_x && x < mlx_s->width)
	{
		my_mlx_pixel_put(mlx_s, x, y, color);
		x++;
	}
}

void	print_pl(t_data *mlx_s, int x, int y, int color)
{
	int	goal_y;

	goal_y = y + 5;
	while (y <= goal_y && y < mlx_s->height)
	{
		print_ln(mlx_s, x, y, color);
		y++;
	}
}

void	print_string(t_data *mlx_s, char *s, int y)
{
	int	x;

	x = 0;
	while (*s)
	{
		if (*s == '1')
			print_sq(mlx_s, x, y, create_trgb(0, 214, 137, 16));
		else if (*s == '2')
			print_sq(mlx_s, x, y, 0x0F0000FF);
		else if (*s == '0')
			print_sq(mlx_s, x, y, create_trgb(0, 31, 97, 141));
		s++;
		x += mlx_s->map_s->width;
	}
}
