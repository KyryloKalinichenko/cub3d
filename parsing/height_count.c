/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:33:56 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/19 11:50:30 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

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

static int	cond(char *buff, t_data *mlx_s, int *i)
{
	char	**tab;

	if (!ft_strcmp("", buff))
	{
		free(buff);
		return (0);
	}
	if (line_check(buff))
		return (1);
	tab = ft_split(buff, ' ');
	if (!(tab))
		error(1);
	if (!ft_strcmp(tab[0], "R"))
		read_r(tab, mlx_s);
	else
		*i = in_tab(mlx_s, tab, *i);
	free(buff);
	return (0);
}

/*
** skip function is running the loop for in_tab to read through the file.
**
*/

static void	skip(t_data *mlx_s, int fd)
{
	int		i;
	char	*buff;

	i = -1;
	while (get_next_line(fd, &buff) > 0 || i > 6)
	{
		if (cond(buff, mlx_s, &i))
			break ;
	}
	if (i < 6 || i > 6)
		error (2);
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
	k = 1;
	fd = open(file, O_RDONLY);
	if (!fd)
		error(3);
	skip(mlx_s, fd);
	mlx_s->side[7] = NULL;
	while (k != 0)
	{
		k = get_next_line(fd, &buff);
		if (!line_check(buff) || (k == 1 && !ft_strcmp("", buff)))
			error(2);
		if ((int)ft_strlen(buff) > (int)mlx_s->map_s->mapX)
			mlx_s->map_s->mapX = ft_strlen(buff);
		height++;
		free(buff);
	}
	if (0 > close (fd))
		error(4);
	return (height + 1);
}
