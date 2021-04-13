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
    int width = (mlx_s->width / 2);
    int height = (mlx_s->height / 2);
     
    printf("width %i, height %i \n", width, height);
    //img = mlx_new_image(mlx_s->mlx, mlx_s->width, mlx_s->height);
    mlx_s->text_img = mlx_xpm_file_to_image(mlx_s->mlx, "./bomb.xpm", &width, &height);
    //mlx_put_image_to_window(mlx_s->mlx, mlx_s->mlx_win, mlx_s->text_img, 200, 200);
    
}

void    put_text(int drawStart, int drawEnd, int i, t_data *mlx_s, int perpWallDist)
{
    char texNum = mlx_s->map_s->map[(int)mlx_s->ray->on_map->x][(int)mlx_s->ray->on_map->y]; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (mlx_s->ray->side == 0)
        wallX = mlx_s->ray->on_map->y + perpWallDist * mlx_s->ray->ray_dir->y;
      else
        wallX = mlx_s->ray->on_map->x + perpWallDist * mlx_s->ray->ray_dir->x;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(mlx_s->width));
      if(mlx_s->ray->side == 0 && mlx_s->ray->ray_dir->x > 0) texX = mlx_s->width - texX - 1;
      if(mlx_s->ray->side == 1 && mlx_s->ray->ray_dir->y < 0) texX = mlx_s->width - texX - 1;
       double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y<drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        Uint32 color = texture[texNum][texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
      }
}