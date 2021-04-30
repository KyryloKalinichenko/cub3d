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
	while (line[++i] && (line[i] == '1' || line[i] == ' '))
		;
	if (line[i])
		map_err();
}

static void	point_check(char **map, int i, int j, t_point *start, int len)
{
	//printf("%c\n", map[i][j]);
	if (map[i][j] == '0' || map[i][j] == '2' || map[i][j] == 'W' ||
	map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'E')
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
	int	i;
	int	j;
	int len;
	short fl;

	i = 0;
	j = 0;
	fl = 0;
	//printf("%s OK\n", map[i]);
	check_first_last(map[i++]);
	//printf("first OK\n");
	//start->x = -1; 
	//start->y = -1;
	while (map[i] != '\0' && map[i] && i < (last - 1))
	{
		len = ft_strlen(map[i]);
		printf("%s OK %10i\n", map[i], last);
		while (map[i][j])
		{
			point_check(map, i, j, start, len);
			j++;
		}
		j = 0;
		i++;
	}
	//printf("%s OK\n", map[i]);
	check_first_last(map[i]);
	//printf("%10f, %10f %10c\n", start->x, start->y, start->point);
	if (start->x < 0 || start->y < 0)
		map_err();
	//printf("%s OK\n", map[i]);
}

int	s_count(char **map)
{
	int i;
	int j;
	int count;

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

t_sprite	*s_place(char **map)
{
	int i;
	int j;
	int count;
	t_sprite *here;

	i = -1;
	j = -1;
	count = 0;
	here = malloc(sizeof(t_sprite));
	while (map[++i])
	{	
		while (map[i][++j])
		{
			if (map[i][j] == '2')
			{
				here->x = j + 0.5;
				here->y = i + 0.5;				
				count++;
			}
		}
		j = -1;
	}
	return (here);
}