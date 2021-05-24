/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:48:29 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/19 11:54:34 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

/*
** init_mlx make a connection to the display and create 
** a window with all necessary variables by mlx_lib. 
**
*/

static void	init_mlx(t_data *mlx_s)
{
	int	i;

	i = -1;
	mlx_s->mlx = mlx_init();
	if (!mlx_s->mlx)
		error(1);
	mlx_s->mlx_win = mlx_new_window(mlx_s->mlx,
				mlx_s->width, mlx_s->height, "The cub is here!");
	if (!mlx_s->mlx_win)
		error(1);
	mlx_s->img = mlx_new_image(mlx_s->mlx, mlx_s->width, mlx_s->height);
	if (!mlx_s->img)
		error(1);
	mlx_s->addr = mlx_get_data_addr(mlx_s->img,
			&mlx_s->bits_per_pixel, &mlx_s->line_length, &mlx_s->endian);
	mlx_s->zbuffer = malloc(sizeof(double *) * mlx_s->width);
	mlx_s->spriteNum = s_count(mlx_s->map_s->map);
	mlx_s->sprite = malloc(sizeof(t_sprite *) * mlx_s->spriteNum);
	if (!mlx_s->sprite || !mlx_s->zbuffer)
		error(1);
	s_place(mlx_s->map_s->map, mlx_s->sprite);
}

/*
** Read resolution and conver it into two int. 
**
*/

static int	num(char *str)
{
	while (*str && (ft_isdigit(*str) || ft_iswhitespace(*str)))
		str++;
	if (*str)
		error(2);
	return (1);
}

static void	res_test(t_data *mlx_s)
{
	int	new_width;
	int	new_height;

	new_height = mlx_s->height;
	new_width = mlx_s->width;
	mlx_get_screen_size(mlx_s, &new_width, &new_height);
	if (new_width < mlx_s->width || !(mlx_s->width))
		mlx_s->width = new_width - 1;
	if (new_height < mlx_s->height || !(mlx_s->height))
		mlx_s->height = new_height - 1;
}

void	read_r(char **tab, t_data *mlx_s)
{
	int	i;

	if (!tab[1] || !tab[2] || mlx_s->width != 0 || mlx_s->height != 0)
		error(2);
	i = -1;
	while (tab[++i])
	{
		if (i == 1 && num(tab[i]))
			mlx_s->width = ft_atoi(tab[i]);
		else if (i == 2 && num(tab[i]))
			mlx_s->height = ft_atoi(tab[i]);
		free(tab[i]);
		if (i > 2)
			error(2);
	}
	free(tab);
	if (mlx_s->width <= 0 || mlx_s->height <= 0)
		error(2);
	res_test(mlx_s);
}

int	init(t_data *mlx_s, char *file)
{
	t_map	*map_s;
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	map_s = malloc(sizeof(t_map));
	mlx_s->tex = malloc(sizeof(t_sides));
	map_s->start = malloc(sizeof(t_point));
	if (!map_s || !ray || !mlx_s->tex || !map_s->start)
		error(1);
	map_s->start->y = -1;
	map_s->start->x = -1;
	mlx_s->map_s = map_s;
	mlx_s->width = 0;
	mlx_s->height = 0;
	map_s->mapX = 0;
	parsing_map(file, mlx_s);
	check_map(mlx_s->map_s->map, mlx_s->map_s->mapY,
		mlx_s->map_s->start, mlx_s->map_s->mapX);
	init_mlx(mlx_s);
	mlx_s->ray = ray;
	textures(mlx_s, mlx_s->tex);
	init_ray(ray, map_s->start);
	return (0);
}
