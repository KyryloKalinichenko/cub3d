/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:01:16 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/04 13:07:03 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

/*
** The \"move\" function is calling when any key are pressed,
** implement changes and call the functions to update the frame.
**
*/

int	cmp_double(t_point a, t_point b)
{
	if (a.x != b.x && a.y != b.y)
		return (0);
	else
		return (1);
}

static int	move(t_data *mlx_s)
{
	static t_point pos;
	static t_point dir;
	static t_point plane;

	if (cmp_double(pos, *mlx_s->ray->pos) 
		&& cmp_double(dir, *mlx_s->ray->dir) && cmp_double(plane, *mlx_s->ray->plane))
		return (0);
	else
	{
		pos = *mlx_s->ray->pos;
		dir = *mlx_s->ray->dir;
		plane = *mlx_s->ray->plane;
		return (1);
	}
}

static void	check_type(char *filename)
{
	char	**tab;
	int		i;

	tab = ft_split(filename, '.');
	if (!tab)
		error(1);
	i = open(filename, O_RDONLY);
	if (!tab[1] || ft_strcmp("cub", tab[1]) || i < 0)
		wrong_flag();
	tab_free(tab);
}

void change(t_data *mlx_s)
{
	if (((mlx_s->fl & 16) >> 4) == 1)
		turn_r(mlx_s->ray);
	if (((mlx_s->fl & 32) >> 5) == 1)
		turn_l(mlx_s->ray);
	if ((mlx_s->fl & 1) == 1)
		back_forth(mlx_s, BACK);
	if (((mlx_s->fl & 2) >> 1) == 1)
		back_forth(mlx_s, FORTH);;
	if (((mlx_s->fl & 4) >> 2) == 1)
		left_right(mlx_s, LEFT, mlx_s->map_s->map);
	if (((mlx_s->fl & 8) >> 3) == 1)
		left_right(mlx_s, RIGHT, mlx_s->map_s->map);
}

int	next_frame(t_data *mlx_s)
{
	change(mlx_s);
	if (!move(mlx_s))
		return (1);
	ray_fun(mlx_s, mlx_s->ray);
	mlx_put_image_to_window(mlx_s->mlx, mlx_s->mlx_win, mlx_s->img, 0, 0);
	system("sleep 0.01");
	return (0);
}

int flags(int keycode, t_data *mlx_s)
{
	if (keycode == TLEFT && ((mlx_s->fl & 16) >> 4) != 1)
		mlx_s->fl += 16;
	if (keycode == TRIGHT && ((mlx_s->fl & 32) >> 5) != 1)
		mlx_s->fl += 32;
	if (keycode == BACK && (mlx_s->fl & 1) != 1)
		mlx_s->fl += 1;
	if (keycode == FORTH && ((mlx_s->fl & 2) >> 1) != 1)
		mlx_s->fl += 2;
	if (keycode == LEFT && ((mlx_s->fl & 4) >> 2) != 1)
		mlx_s->fl += 4;
	if (keycode == RIGHT && ((mlx_s->fl & 8) >> 3) != 1)
		mlx_s->fl += 8;
	if (keycode == ESC)
		just_exit();
	//change(mlx_s);
	return (0);
}

int	nothing(int keycode, int *i)
{
	if (keycode == TLEFT && ((*i & 16) >> 4) == 1)
		*i -= 16;
	if (keycode == TRIGHT && ((*i & 32) >> 5) == 1)
		*i -= 32;
	if (keycode == BACK && (*i & 1) == 1)
		*i -= 1;
	if (keycode == FORTH && ((*i & 2) >> 1) == 1)
		*i -= 2;
	if (keycode == LEFT && ((*i & 4) >> 2) == 1)
		*i -= 4;
	if (keycode == RIGHT && ((*i & 8) >> 3) == 1)
		*i -= 8;
	return (0);
}

/*
** The main function for my project. Here the main loop is 
** running and all other functions are calling.  
*/

int	main(int argc, char **argv)
{
	t_data	mlx_s;

	if (argc == 1 || argc > 3)
		return (printf("ArgError\n"));
	check_type(argv[1]);
	init(&mlx_s, argv[1]);
	//next_frame(&mlx_s);
	if (argc == 3)
	{
		if (!ft_strcmp("--save", argv[2]))
			save_image(&mlx_s);
		else
			wrong_flag();
	}
	mlx_hook (mlx_s.mlx_win, 2, 1L << 0, flags, &mlx_s);
	mlx_hook (mlx_s.mlx_win, 3, 1L << 1, nothing, &mlx_s.fl);
	//change(&mlx_s);
	mlx_hook (mlx_s.mlx_win, 17, 1L << 17, just_exit, &mlx_s);
	mlx_loop_hook(mlx_s.mlx, next_frame, &mlx_s);
	mlx_loop (mlx_s.mlx);
}
