/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:01:30 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/14 14:04:33 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

static void	check_first_last(char *line)
{
	int	i;

	i = -1;
	if (line)
	{
		while (line[++i] && (line[i] == '1' || line[i] == ' '))
			;
		if (line[i])
			error(2);
	}
	else
		error(2);
}

static void	start_ver(int i, int j, t_point *start, char **map)
{
	if (start->x == -1 && start->y == -1)
	{
		start->x = j + 0.5;
		start->y = i + 0.5;
		start->point = map[i][j];
		map[i][j] = '0';
	}
	else
		error(2);
}

static void	point_check(char **map, t_on_map pos, t_point *start, int len)
{
	if (map[pos.x][pos.y] == '0' || map[pos.x][pos.y] == '2'
	|| map[pos.x][pos.y] == 'W' || map[pos.x][pos.y] == 'S'
	|| map[pos.x][pos.y] == 'N' || map[pos.x][pos.y] == 'E')
	{
		if (map[pos.x][pos.y] != '2' && map[pos.x][pos.y] != '0')
			start_ver(pos.x, pos.y, start, map);
		if (pos.y == 0 || pos.y == (len - 1))
			error(2);
		if (map[pos.x][pos.y + 1] == ' ' || map[pos.x][pos.y - 1] == ' ')
			error(2);
		if (map[pos.x + 1][pos.y + 1] == ' '
		|| map[pos.x - 1][pos.y - 1] == ' ')
			error(2);
		if (map[pos.x - 1][pos.y + 1] == ' '
		|| map[pos.x + 1][pos.y - 1] == ' ')
			error(2);
		if (map[pos.x + 1][pos.y] == ' ' || map[pos.x - 1][pos.y] == ' ')
			error(2);
	}
}

void	check_map(char **map, int last, t_point *start, int len)
{
	t_on_map	pos;
	short		fl;

	pos.x = -1;
	pos.y = 0;
	fl = 0;
	check_first_last(map[++pos.x]);
	while (map[++pos.x] != NULL && pos.x <= (last - 2))
	{
		while (map[pos.x][pos.y])
		{
			point_check(map, pos, start, len);
			pos.y++;
		}
		pos.y = 0;
	}
	check_first_last(map[pos.x - 1]);
	if (start->x < 0 || start->y < 0)
		error(2);
}

t_sprite	*put_s_place(int i, int j)
{
	t_sprite	*here;

	here = malloc(sizeof(t_sprite));
	if (!here)
		error(1);
	here->x = j + 0.5;
	here->y = i + 0.5;
	here->tex = NULL;
	return (here);
}
