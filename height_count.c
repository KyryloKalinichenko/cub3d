/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:33:56 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/04 15:01:37 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

/*
** in_tab is looking for particular lines and strings
** and store them in side arr.
*/

static int	in_tab(t_data *mlx_s, char **tab, int i)
{
	if (!ft_strcmp(tab[0], "NO") && tab[1])
		mlx_s->side[++i] = tab;
	else if (!ft_strcmp(tab[0], "SO") && tab[1])
		mlx_s->side[++i] = tab;
	else if (!ft_strcmp(tab[0], "WE") && tab[1])
		mlx_s->side[++i] = tab;
	else if (!ft_strcmp(tab[0], "EA") && tab[1])
		mlx_s->side[++i] = tab;
	else if (!ft_strcmp(tab[0], "S") && tab[1])
		mlx_s->side[++i] = tab;
	else if (!ft_strcmp(tab[0], "F") && tab[1])
		mlx_s->side[++i] = tab;
	else if (!ft_strcmp(tab[0], "C") && tab[1])
		mlx_s->side[++i] = tab;
	else if (!ft_strcmp(tab[0], "S") && tab[1])
		mlx_s->side[++i] = tab;
	return (i);
}

/*
** skip function is running the loop for in_tab to read through the file.
**
*/

static void	skip(t_data *mlx_s, int fd)
{
	int		i;
	char	*buff;
	char	**tab;

	i = -1;
	while (get_next_line(fd, &buff) > 0)
	{
		if (!ft_strcmp("", buff))
		{
			free(buff);
			continue ;
		}
		if (line_check(buff))
			break ;
		if (!(tab
				= ft_split(buff, ' ')))
			error(1);
		if (!ft_strcmp(tab[0], "R"))
			read_r(tab, mlx_s);
		else
			i = in_tab(mlx_s, tab, i);
		free(buff);
	}
	free(buff);
}

/*
** The height_count performs counting the number of rows
** and reads textures, resolution, floor and ceiling colors.
**
*/

int	height_count(char *file, t_data *mlx_s)
{
	short	height;
	int		fd;
	char	*buff;
	int		k;

	height = 1;
	fd = open(file, O_RDONLY);
	if (!fd)
		error(3);
	skip(mlx_s, fd);
	mlx_s->side[7] = NULL;
	while (1)
	{
		k = get_next_line(fd, &buff);
		if (!line_check(buff))
			map_err();
		height++;
		free(buff);
		if (k == 0)
			break ;
	}
	close (fd);
	return (height + 1);
}
