/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_cheking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:19:03 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/08 17:22:47 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

static int	get_col(char *line)
{
	char	**tab;
	int		i;
	int		r;
	int		g;
	int		b;

	tab = ft_split(line, ',');
	i = -1;
	if (!tab)
		malloc_error();
	while (tab[++i])
	{
		if (i == 0)
			r = ft_atoi(tab[i]);
		else if (i == 1)
			g = ft_atoi(tab[i]);
		else if (i == 2)
			b = ft_atoi(tab[i]);
	}
	if (i > 3 || i < 3 || r < 0 || g < 0 || b < 0)
		map_err();
	tab_free(tab);
	return (create_trgb(0, r, g, b));
}

static void	statement(t_data *mlx_s, int i, int *flag, int *flag2)
{
	if (!ft_strcmp(mlx_s->side[i][0], "NO"))
		*flag += NO;
	if (!ft_strcmp(mlx_s->side[i][0], "WE"))
		*flag += WE;
	if (!ft_strcmp(mlx_s->side[i][0], "EA"))
		*flag += EA;
	if (!ft_strcmp(mlx_s->side[i][0], "SO"))
		*flag += SO;
	if (!ft_strcmp(mlx_s->side[i][0], "C"))
		*flag += C;
	if (!ft_strcmp(mlx_s->side[i][0], "F"))
		*flag2 += F;
	if (!ft_strcmp(mlx_s->side[i][0], "S"))
		*flag2 += S;
}

static void	side_check(t_data *mlx_s)
{
	int	i;
	int	flag;
	int	flag2;

	i = -1;
	flag = 0;
	flag2 = 0;
	while (mlx_s->side[++i])
		statement(mlx_s, i, &flag, &flag2);
	if (flag != 31 || flag2 != 96)
		map_err();
}

void	textures(t_data *mlx_s, t_sides *tex)
{
	int	i;

	i = -1;
	side_check(mlx_s);
	while (mlx_s->side[++i])
	{
		if (!ft_strcmp(mlx_s->side[i][0], "NO"))
			tex->no_side = init_text(mlx_s, mlx_s->side[i][1], tex->no_side);
		if (!ft_strcmp(mlx_s->side[i][0], "WE"))
			tex->we_side = init_text(mlx_s, mlx_s->side[i][1], tex->we_side);
		if (!ft_strcmp(mlx_s->side[i][0], "EA"))
			tex->ea_side = init_text(mlx_s, mlx_s->side[i][1], tex->ea_side);
		if (!ft_strcmp(mlx_s->side[i][0], "SO"))
			tex->so_side = init_text(mlx_s, mlx_s->side[i][1], tex->so_side);
		if (!ft_strcmp(mlx_s->side[i][0], "C"))
			mlx_s->cel = get_col(mlx_s->side[i][1]);
		if (!ft_strcmp(mlx_s->side[i][0], "F"))
			mlx_s->floor = get_col(mlx_s->side[i][1]);
		if (!ft_strcmp(mlx_s->side[i][0], "S"))
			tex->sprite = init_text(mlx_s, mlx_s->side[i][1], tex->sprite);
	}
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
