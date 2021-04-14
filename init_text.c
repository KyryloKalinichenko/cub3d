/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 10:33:01 by kkalinic          #+#    #+#             */
/*   Updated: 2021/04/13 10:33:03 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_head.h"

void init_text(t_data *mlx_s)
{
    int width = 600;
    int height = 500;
     
    printf("width %i, height %i \n", width, height);
    mlx_s->tex = malloc((sizeof(t_tex)));
    if (!mlx_s->tex)
      malloc_error();
    //img = mlx_new_image(mlx_s->mlx, mlx_s->width, mlx_s->height);
    mlx_s->tex->img = mlx_xpm_file_to_image(mlx_s->mlx, "./bomb.xpm", &width, &height);
    mlx_s->tex->addr = mlx_get_data_addr(mlx_s->tex->img, &mlx_s->tex->bits_per_pixel, &mlx_s->tex->line_length,
                                 &mlx_s->tex->endian);
    //mlx_put_image_to_window(mlx_s->mlx, mlx_s->mlx_win, mlx_s->text_img, 200, 200);
    
}

void    put_text(int drawStart, int drawEnd, int i, t_data *mlx_s, int lineHeight, int perpWallDist)
{
    //char texNum = mlx_s->map_s->map[(int)mlx_s->ray->on_map->x][(int)mlx_s->ray->on_map->y]; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (mlx_s->ray->side == 0)
        wallX = mlx_s->ray->pos->y + perpWallDist * mlx_s->ray->ray_dir->y;
      else
        wallX = mlx_s->ray->pos->x + perpWallDist * mlx_s->ray->ray_dir->x;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(mlx_s->width));
      if(mlx_s->ray->side == 0 && mlx_s->ray->ray_dir->x > 0)
        texX = mlx_s->width - texX - 1;
      if(mlx_s->ray->side == 1 && mlx_s->ray->ray_dir->y < 0)
        texX = mlx_s->width - texX - 1;

       double step = 1.0 * 500 / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - mlx_s->height / 2 + lineHeight / 2) * step;
      int texY;
      unsigned int color = 0;
      int y = drawStart;
      //printf("x - %i\n y - %i\n  xt - %i\n yt - %i\n", i, y, texX, texY);
      while(y++ < (int)drawEnd - 1)
      {
        texY = (int)texPos & (500 - 1);
        texPos += step;
       //printf(" xt - %i\n yt - %i\n", texX, texY);
        mlx_pixel_get(mlx_s->tex, texX, texY, &color);
        //printf("color - %i\n", color);
        my_mlx_pixel_put(mlx_s, i, y, color);
          //printf("wow\n");
      }
}