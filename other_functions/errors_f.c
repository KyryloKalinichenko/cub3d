/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:10:56 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/19 11:53:31 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

int	just_exit(void)
{
	printf("See you soon!\n");
	system("killall afplay");
	exit(EXIT_SUCCESS);
}

void	error(int code)
{
	system("killall afplay");
	if (code == 1)
		printf("Error\nMalloc or FD  error!\n");
	else if (code == 2)
		printf("Error\nBad map!\n");
	else if (code == 3)
		printf("Error\nNo such a file or directory!\n");
	else if (code == 4)
		printf("Error\nClose err!\n");
	else if (code == 5)
		printf("Error\nNo such a flag or argument!\n");
	exit(EXIT_FAILURE);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	find_max(char **map)
{
	int	i;
	int	tmp;
	int	max;

	i = -1;
	max = ft_strlen(map[++i]);
	while (map[++i])
	{
		if (max
			< (tmp = ft_strlen(map[i])))
			max = tmp;
	}
	return (max);
}

char	*fill_line(char *line, int max)
{
	int		i;
	char	*point;
	int		limit;
	char	*tmp;

	i = -1;
	limit = ft_strlen(line);
	tmp = line;
	point = malloc(sizeof(char) * (max + 1));
	while (++i < max)
	{
		if (i < limit)
			point[i] = line[i];
		else
			point[i] = ' ';
	}
	point[i] = '\0';
	line = point;
	return (point);
}
