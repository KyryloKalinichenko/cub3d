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
** Two following functions performs players movements
** and ensures that there is no wall on the way. 
**
*/

static void	back_forth(t_data *mlx_s, int keycode)
{
	if (keycode == FORTH)
	{
		if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->y + mlx_s->ray->dir->y
				* (MSPEED + 0.1))][(int)(mlx_s->ray->pos->x)] == '0')
			mlx_s->ray->pos->y += mlx_s->ray->dir->y * MSPEED;
		if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->y)][(int)
			(mlx_s->ray->pos->x + mlx_s->ray->dir->x * (MSPEED + 0.1))] == '0')
			mlx_s->ray->pos->x += mlx_s->ray->dir->x * MSPEED;
	}
	else if (keycode == BACK)
	{
		if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->y - mlx_s->ray->dir->y
				* (MSPEED + 0.1))][(int)(mlx_s->ray->pos->x)] == '0')
			mlx_s->ray->pos->y -= mlx_s->ray->dir->y * MSPEED;
		if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->y)][(int)
			(mlx_s->ray->pos->x - mlx_s->ray->dir->x * (MSPEED + 0.1))] == '0')
			mlx_s->ray->pos->x -= mlx_s->ray->dir->x * MSPEED;
	}
}

static void	left_right(t_data *mlx_s, int keycode, char **map)
{
	double	r_p_x;
	double	r_p_y;
	double	r_d_x;
	double	r_d_y;

	r_d_x = mlx_s->ray->dir->x;
	r_d_y = mlx_s->ray->dir->y;
	r_p_x = mlx_s->ray->pos->x;
	r_p_y = mlx_s->ray->pos->y;
	if (keycode == LEFT)
	{
		if (map[(int)(r_p_y + r_d_x * (MSPEED))][(int)(r_p_x)] == '0')
			mlx_s->ray->pos->y += r_d_x * MSPEED;
		if (map[(int)(r_p_y)]
				[(int)(r_p_x - r_d_y * (MSPEED))] == '0')
			mlx_s->ray->pos->x -= r_d_y * MSPEED;
	}
	else if (keycode == RIGHT)
	{
		if (map[(int)(r_p_y - r_d_x * (MSPEED + 0.1))]
			[(int)(r_p_x)] == '0')
			mlx_s->ray->pos->y -= r_d_x * MSPEED;
		if (map[(int)(r_p_y)][(int)(r_p_x + r_d_y * (MSPEED))] == '0')
			mlx_s->ray->pos->x += r_d_y * MSPEED;
	}
}

/*
** The \"move\" function is calling when any key are pressed,
** implement changes and call the functions to update the frame.
**
*/

static int	move(int keycode, t_data *mlx_s)
{
	back_forth(mlx_s, keycode);
	left_right(mlx_s, keycode, mlx_s->map_s->map);
	if (keycode == TLEFT)
		turn_r(mlx_s->ray);
	else if (keycode == TRIGHT)
		turn_l(mlx_s->ray);
	else if (keycode == ESC)
		just_exit();
	ray_fun(mlx_s, mlx_s->ray);
	mlx_put_image_to_window(mlx_s->mlx, mlx_s->mlx_win, mlx_s->img, 0, 0);
	return (0);
}

static void	check_type(char *filename)
{
	char	**tab;
	int		i;

	i = -1;
	tab = ft_split(filename, '.');
	if (!tab)
		malloc_error();
	if (!tab[1] || ft_strcmp("cub", tab[1]))
		wrong_flag();
	tab_free(tab);
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
	move(0, &mlx_s);
	if (argc == 3)
	{
		if (!ft_strcmp("--save", argv[2]))
			save_image(&mlx_s);
		else
			wrong_flag();
	}
	mlx_hook (mlx_s.mlx_win, 2, 1L << 0, move, &mlx_s);
	mlx_hook (mlx_s.mlx_win, 17, 1L << 17, just_exit, &mlx_s);
	mlx_loop (mlx_s.mlx);
}
