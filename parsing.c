/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:33:09 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/08 16:52:30 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

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

static void	extra(t_data *mlx_s, int fd, char **map, int i)
{
	int		f;

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
}
/*
** The main parsing function.
**
*/

void	parsing_map(char *file, t_data *mlx_s)
{
	int		fd;
	int		i;
	char	**map;

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
		error(1);
	mlx_s->map_s->map = map;
	while (get_next_line(fd, &map[i]))
	{
		if (ft_strcmp(map[i], "") && line_check(map[i]))
			break ;
		free(map[i]);
	}
	extra(mlx_s, fd, map, i);
	close (fd);
}
