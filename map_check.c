/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:01:30 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/04 17:43:28 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

static void	check_first_last(char *line)
{
	int	i;

	i = -1;
	if (line)
	{
		while (line[++i] && (line[i] == '1' || line[i] == ' '))
			;
		if (line[i])
			map_err();
	}
	else
		map_err();
}

static void	point_check(char **map, int i, int j, t_point *start, int len)
{
	if (map[i][j] == '0' || map[i][j] == '2' || map[i][j] == 'W'
			|| map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'E')
	{
		if (map[i][j] != '2' && map[i][j] != '0')
		{
			if (start->x == -1 && start->y == -1)
			{
				start->x = j + 0.5;
				start->y = i + 0.5;
				start->point = map[i][j];
				map[i][j] = '0';
			}
			else
				map_err();
		}
		if (j == 0 || j == (len - 1))
			map_err();
		if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
			map_err();
		if (map[i + 1][j + 1] == ' ' || map[i - 1][j - 1] == ' ')
			map_err();
		if (map[i - 1][j + 1] == ' ' || map[i + 1][j - 1] == ' ')
			map_err();
		if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
			map_err();
	}
}

void	check_map(char **map, int last, t_point *start)
{
	int		i;
	int		j;
	int		len;
	short	fl;

	i = -1;
	j = 0;
	fl = 0;
	check_first_last(map[++i]);
	while (map[++i] != '\0' && map[i] && i < last)
	{
		len = ft_strlen(map[i]);
		while (map[i][j])
		{
			point_check(map, i, j, start, len);
			j++;
		}
		if (!ft_strcmp(map[i], ""))
			check_first_last(map[i - 1]);
		j = 0;
	}
	if (start->x < 0 || start->y < 0)
		map_err();
}

int	s_count(char **map)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = -1;
	count = 0;
	while (map[++i])
	{	
		while (map[i][++j])
		{
			if (map[i][j] == '2')
				count++;
		}
		j = -1;
	}
	return (count);
}

void	s_place(char **map, t_sprite **sprites)
{
	int			i;
	int			j;
	int			n;
	t_sprite	*here;

	i = -1;
	j = -1;
	n = 0;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '2')
			{
				here = malloc(sizeof(t_sprite));
				if (!here)
					malloc_error();
				here->x = j + 0.5;
				here->y = i + 0.5;
				here->tex = NULL;
				sprites[n] = here;
				n++;
			}
		}
		j = -1;
	}
}
