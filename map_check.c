/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:01:30 by kkalinic          #+#    #+#             */
/*   Updated: 2021/04/12 14:10:27 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_head.h"

static void	check_first_last(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && (line[i] != '1' || line[i] != ' '))
		;
	if (line[i])
		map_err();
}

static void	point_check(char **map, int i, int j)
{
	if (map[i][j] == '0' || map[i][j] == '2')
	{
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

void	check_col(char **map, int last)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	check_first_last(map[i++]);
	while (map[i] && map[i][j] && i < (last - 2))
	{
		while (map[i][j])
		{
			point_check(map, i, j);
			j++;
		}
		j = 0;
		i++;
	}
	check_first_last(map[i]);
}

void	check_map(char **map, int last)
{
	check_col(map, last);
}
