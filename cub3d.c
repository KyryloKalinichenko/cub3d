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

/*
** The main function for my project. Here the main loop running and all other functions is calling.  
*/

int    move(int keycode, t_data *mlx_s)
{
    //printf("%i\n", keycode);
    if (keycode == FORTH)
    {
        /*mlx_s->player.y += mlx_s->player.dy;
        mlx_s->player.x += mlx_s->player.dx;*/
        if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->x + mlx_s->ray->dir->x * (MSPEED + 0.2))][(int)(mlx_s->ray->pos->y)] == '0')
            mlx_s->ray->pos->x += mlx_s->ray->dir->x * MSPEED;
        if (mlx_s->map_s->map[(int)(mlx_s->ray->pos->x)][(int)(mlx_s->ray->pos->y + mlx_s->ray->dir->y * (MSPEED + 0.2))] == '0')
            mlx_s->ray->pos->y += mlx_s->ray->dir->y * MSPEED;
    }
    if (keycode == BACK)
    {   /*
        mlx_s->player.y -= mlx_s->player.dy;
        mlx_s->player.x -= mlx_s->player.dx;*/
        if(mlx_s->map_s->map[(int)(mlx_s->ray->pos->x - mlx_s->ray->dir->x * (MSPEED + 0.2))][(int)(mlx_s->ray->pos->y)] == '0')
            mlx_s->ray->pos->x -= mlx_s->ray->dir->x * MSPEED;
        if(mlx_s->map_s->map[(int)(mlx_s->ray->pos->x)][(int)(mlx_s->ray->pos->y - mlx_s->ray->dir->y * (MSPEED + 0.2))] == '0')
            mlx_s->ray->pos->y -= mlx_s->ray->dir->y * MSPEED;
    }
    if (keycode == LEFT)
    {
        turn_l(mlx_s->ray);
       // mlx_s->player.dx = mlx_s->ray->dir->x * 3;
       // mlx_s->player.dy = mlx_s->ray->dir->y * 3;
    }
    if (keycode == RIGHT)
    {
        turn_r(mlx_s->ray);
        //mlx_s->player.dx = mlx_s->ray->dir->x * 3;
        //mlx_s->player.dy = mlx_s->ray->dir->y * 3;
    }
    if (keycode == ESC)
        just_exit();
    printf("x =  %f\n", mlx_s->ray->pos->x);
	printf("y =  %f\n", mlx_s->ray->pos->y);
    //printf("%i\n", keycode);
    //mlx_s->ray->pos->x = ((mlx_s->player.x + (mlx_s->map_s->width / 2)) / mlx_s->map_s->width);
    //mlx_s->ray->pos->y = ((mlx_s->player.y + (mlx_s->map_s->height / 2)) / mlx_s->map_s->height);
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
    mlx_hook (mlx_s.mlx_win, 2, 1L<<0, move, &mlx_s);
    mlx_loop(mlx_s.mlx);
}
