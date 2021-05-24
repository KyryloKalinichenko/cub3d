/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:15:57 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/13 16:42:02 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

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
