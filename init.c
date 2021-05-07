/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:48:29 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/04 17:31:29 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_head.h"

/*
** init_mlx make a connection to the display and create 
** a window with all necessary variables by mlx_lib. 
**
*/

static void	init_mlx(t_data *mlx_s)
{
	int i;

	i = -1;
	mlx_s->mlx = mlx_init();
	mlx_s->mlx_win = mlx_new_window(mlx_s->mlx,
			mlx_s->width, mlx_s->height, "The cub is here!");
	mlx_s->img = mlx_new_image(mlx_s->mlx, mlx_s->width, mlx_s->height);
	mlx_s->addr = mlx_get_data_addr(mlx_s->img,
			&mlx_s->bits_per_pixel, &mlx_s->line_length, &mlx_s->endian);
	mlx_s->zbuffer = malloc(sizeof(double *) * mlx_s->width);
	mlx_s->spriteNum = s_count(mlx_s->map_s->map);
	mlx_s->sprite = malloc(sizeof(t_sprite *) * mlx_s->spriteNum);
	if (!mlx_s->sprite || !mlx_s->zbuffer)
		malloc_error();
	s_place(mlx_s->map_s->map, mlx_s->sprite);
}

/*
** Read resolution and conver it into two int. 
**
*/

static int	num(char *str)
{
	while (*str && ft_isdigit(*str))
		str++;
	if (*str)
		map_err();
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
		mlx_s->width = new_width;
	if (new_height < mlx_s->height || !(mlx_s->height))
		mlx_s->height = new_height;
}

void	read_r(char **tab, t_data *mlx_s)
{
	int	i;

	if (mlx_s->width != 0 || mlx_s->height != 0)
		map_err();
	i = -1;
	while (tab[++i])
	{
		if (i == 1 && num(tab[i]))
			mlx_s->width = ft_atoi(tab[i]);
		else if (i == 2 && num(tab[i]))
			mlx_s->height = ft_atoi(tab[i]);
		free(tab[i]);
		if (i > 2)
			map_err();
	}
	free(tab);
	if (!mlx_s->width || !mlx_s->height)
		map_err();
	res_test(mlx_s);
}

/*
** Count height of the map. Return int. 
**
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	char_check(char c)
{
	char	*here;
	int		i;

	here = "012WSEN ";
	i = -1;
	while (here[++i])
	{
		if (here[i] == c)
			return (1);
	}
	return (0);
}

int	line_check(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!char_check(line[i]))
			return (0);
	}
	return (1);
}

/*
** The main parsing function. 
**
*/

static int	parsing_map(char *file, t_data *mlx_s)
{
	int		fd;
	int		i;
	char	**map;
	int		f;

	i = 0;
	fd = open(file, O_RDONLY);
	if (!fd)
		no_file();
	if ((mlx_s->map_s->mapY
			= (height_count(file, mlx_s))) == 2 || mlx_s->map_s->mapY < 3)
		map_err();
	mlx_s->map_s->height = mlx_s->height / (mlx_s->map_s->mapY * MINIMAP_S);
	map = malloc(sizeof(char *) * mlx_s->map_s->mapY + 1);
	if (!map)
		malloc_error();
	mlx_s->map_s->map = map;
	while (get_next_line(fd, &map[i]))
	{
		if (ft_strcmp(map[i], "") && line_check(map[i]))
			break ;
		free(map[i]);
	}
	mlx_s->map_s->mapX = ft_strlen(map[i]);
	f = (mlx_s->map_s->mapY + i - 1);
	if (f == i)
		map_err();
	while (f != i)
	{
		get_next_line(fd, &map[++i]);
		if (mlx_s->map_s->mapX < (int)ft_strlen(map[i]))
			mlx_s->map_s->mapX = ft_strlen(map[i]);
	}
	map[i] = NULL;
	mlx_s->map_s->mapS = mlx_s->map_s->mapX * mlx_s->map_s->mapY;
	mlx_s->map_s->width = mlx_s->width / (mlx_s->map_s->mapX * 4);
	close (fd);
	return (0);
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
		malloc_error();
	map_s->start->y = -1;
	map_s->start->x = -1;
	mlx_s->map_s = map_s;
	mlx_s->width = 0;
	mlx_s->height = 0;
	parsing_map(file, mlx_s);
	check_map(mlx_s->map_s->map, mlx_s->map_s->mapY, mlx_s->map_s->start);
	init_mlx(mlx_s);
	mlx_s->ray = ray;
	textures(mlx_s, mlx_s->tex);
	init_ray(ray, map_s->start);
	return (0);
}
