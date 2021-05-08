/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:43:37 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/04 17:47:03 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

static void	ft_draw_right_line(t_data *mlx_s, double delta, t_line vector)
{
	if (vector.y == vector.dy)
		delta = 0;
	while (vector.x++ <= vector.dx)
	{
		while (vector.y != vector.dy)
		{
			vector.y += delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
	}
}

static void	ft_draw_left_line(t_data *mlx_s, double delta, t_line vector)
{
	if (vector.y == vector.dy)
		delta = 0;
	while (vector.x-- >= vector.dx)
	{
		while (vector.y != vector.dy)
		{
			vector.y -= delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
	}
}

static void	ft_draw_down_line(t_data *mlx_s, double delta, t_line vector)
{
	my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
	if (vector.x == vector.dx)
		delta = 0;
	while (vector.y-- >= vector.dy)
	{
		while (vector.x != vector.dx)
		{
			vector.x -= delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
	}
}

static void	ft_draw_up_line(t_data *mlx_s, double delta, t_line vector)
{
	if (vector.x == vector.dx)
		delta = 0;
	while (vector.y++ <= vector.dy)
	{
		while (vector.x != vector.dx)
		{
			vector.x += delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
	}
}

void	print_v(t_data *mlx_s, t_line vector)
{
	double	delta;

	delta = fabs(vector.y - vector.dy) - fabs(vector.x - vector.dx);
	if (delta > 0)
	{
		delta = (vector.x - vector.dx) / (vector.y - vector.dy);
		if (vector.y < vector.dy)
			ft_draw_up_line(mlx_s, delta, vector);
		else
			ft_draw_down_line(mlx_s, delta, vector);
	}
	else
	{
		delta = (vector.y - vector.dy) / (vector.x - vector.dx);
		if (vector.x < vector.dx)
			ft_draw_right_line(mlx_s, delta, vector);
		else if (vector.x >= vector.dx)
			ft_draw_left_line(mlx_s, delta, vector);
	}
}
