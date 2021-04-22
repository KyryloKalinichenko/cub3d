/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:01:16 by kkalinic          #+#    #+#             */
/*   Updated: 2021/04/12 14:01:21 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_head.h"

static void back_forth(t_data *mlx_s, int keycode)
{
    if (keycode == FORTH)
    {
        if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->y + mlx_s->ray->dir->y * (MSPEED))][(int)(mlx_s->ray->pos->x)] == '0')
            mlx_s->ray->pos->y += mlx_s->ray->dir->y * MSPEED;
        if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->y)][(int)(mlx_s->ray->pos->x + mlx_s->ray->dir->x * (MSPEED))] == '0')
            mlx_s->ray->pos->x += mlx_s->ray->dir->x * MSPEED;
    }
    else if (keycode == BACK)
    {
        if(mlx_s->map_s->map[(int)(mlx_s->ray->pos->y - mlx_s->ray->dir->y * (MSPEED))][(int)(mlx_s->ray->pos->x)] == '0')
            mlx_s->ray->pos->y -= mlx_s->ray->dir->y * MSPEED;
        if(mlx_s->map_s->map[(int)(mlx_s->ray->pos->y)][(int)(mlx_s->ray->pos->x - mlx_s->ray->dir->x * (MSPEED))] == '0')
            mlx_s->ray->pos->x -= mlx_s->ray->dir->x * MSPEED;
    }
}

static void left_right(t_data *mlx_s, int keycode)
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
        if(mlx_s->map_s->map[(int)(r_p_y + r_d_x * (MSPEED))][(int)(r_p_x)] == '0')
            mlx_s->ray->pos->y += r_d_x * MSPEED;
        if(mlx_s->map_s->map[(int)(r_p_y)][(int)(r_p_x - r_p_y * (MSPEED))] == '0')
            mlx_s->ray->pos->x -= r_d_y * MSPEED;
    }
    else if (keycode == RIGHT)
    {
        if(mlx_s->map_s->map[(int)(r_p_y - r_d_x * (MSPEED + 0.1))][(int)(r_p_x)] == '0')
            mlx_s->ray->pos->y -= r_d_x * MSPEED;
        if(mlx_s->map_s->map[(int)(r_p_y)][(int)(r_p_x + r_d_y * (MSPEED + 0.1))] == '0')
            mlx_s->ray->pos->x += r_d_y * MSPEED;
    }
}

/*
** The main function for my project. Here the main loop running and all other functions is calling.  
*/

static int    move(int keycode, t_data *mlx_s)
{
    //printf("%d\n", keycode);
    mlx_s->up = 0;
    back_forth(mlx_s, keycode);
    left_right(mlx_s, keycode);
    if (keycode == UP)
        mlx_s->up = 1;
    else if (keycode == TLEFT)
        turn_r(mlx_s->ray);
    else if (keycode == TRIGHT)
        turn_l(mlx_s->ray);
    else if (keycode == ESC)
        just_exit();
    print_player(mlx_s);
    mlx_put_image_to_window(mlx_s->mlx, mlx_s->mlx_win, mlx_s->img, 0, 0);
    return(0);
}

int main(int argc, char **argv)
{
    t_data mlx_s;
   
    if (argc == 1)
        return(printf("Error\n"));
    init(&mlx_s, argv[1]);
    //init_text(&mlx_s);
    mlx_hook (mlx_s.mlx_win, 2, 1L<<0, move, &mlx_s);
    mlx_loop(mlx_s.mlx);
}
