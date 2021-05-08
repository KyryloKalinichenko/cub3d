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
