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

static int get_col(char *line)
{
  char **tab;
  int i;
  int r;
  int g;
  int b;

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
  if (i > 3 || i < 3)
    map_err();
  return (create_trgb(0, r, g, b));
}

void textures(t_data *mlx_s, t_sides *tex)
{
  int i;

  i = -1;
  while (++i < 7)
  {
    if(!ft_strcmp(mlx_s->side[i][0], "NO"))
      tex->no_side = init_text(mlx_s, mlx_s->side[i][1], tex->no_side);
    if(!ft_strcmp(mlx_s->side[i][0], "WE"))
      tex->we_side = init_text(mlx_s, mlx_s->side[i][1], tex->we_side);
    if(!ft_strcmp(mlx_s->side[i][0], "EA"))
      tex->ea_side = init_text(mlx_s, mlx_s->side[i][1], tex->ea_side);
    if(!ft_strcmp(mlx_s->side[i][0], "SO"))
      tex->so_side = init_text(mlx_s, mlx_s->side[i][1], tex->so_side);
    if(!ft_strcmp(mlx_s->side[i][0], "C"))
      mlx_s->cel = get_col(mlx_s->side[i][1]);
    if(!ft_strcmp(mlx_s->side[i][0], "F"))
      mlx_s->floor = get_col(mlx_s->side[i][1]);
    if(!ft_strcmp(mlx_s->side[i][0], "S"))
      tex->sprite = init_text(mlx_s, mlx_s->side[i][1], tex->sprite);
  }
}

t_tex *init_text(t_data *mlx_s, char *path, t_tex *tex)
{
    int width = mlx_s->width;
    int height = mlx_s->height;
    
    tex = malloc(sizeof(t_tex));
    if (!tex)
      malloc_error();
    if (!(tex->img = mlx_xpm_file_to_image(mlx_s->mlx, path, &width, &height)))
      malloc_error();
    if (!(tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel, &tex->line_length,
                                 &tex->endian)))
                                 malloc_error();
    return(tex);
}

void    put_text(int drawStart, int drawEnd, int i, t_data *mlx_s, double lineHeight, double perpWallDist, t_tex *tex)
{
      double wallX; //where exactly the wall was hit

      if (mlx_s->ray->side == 0)
        wallX = mlx_s->ray->pos->y + perpWallDist * mlx_s->ray->ray_dir->y;
      else
        wallX = mlx_s->ray->pos->x + perpWallDist * mlx_s->ray->ray_dir->x;
      wallX -= floor(wallX);

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(64));
      if(mlx_s->ray->side == 0 && mlx_s->ray->ray_dir->x > 0)
        texX = 64 - texX - 1;
      if(mlx_s->ray->side == 1 && mlx_s->ray->ray_dir->y < 0)
        texX = 64 - texX - 1;

       double step = 1.0 * 64 / lineHeight;
      double texPos = (drawStart - mlx_s->height / 2 + lineHeight / 2) * step;
      int texY;
      unsigned int color = 0;
      int y = drawStart;
      while(y < (int)drawEnd)
      {
        texY = (int)texPos & (64 - 1);
        texPos += step;
        mlx_pixel_get(tex, texX, texY, &color);
        my_mlx_pixel_put(mlx_s, i, y, color);
          y++;
      }
}

void    print_sprite(t_data *mlx_s, t_ray *ray)
{
    int stripe;
    //sort sprites from far to close
    //t_sprite mlx_s->sprite[mlx_s->spriteNum];
    int spriteOrder[mlx_s->spriteNum];
    double spriteDistance[mlx_s->spriteNum];

    for(int i = 0; i < mlx_s->spriteNum; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = ((ray->pos->x - mlx_s->sprite[i]->x) * (ray->pos->x - mlx_s->sprite[i]->x) + (ray->pos->y - mlx_s->sprite[i]->y) * (ray->pos->y - mlx_s->sprite[i]->y)); //sqrt not taken, unneeded
    }
    //sortSprites(spriteOrder, spriteDistance, numSprites);
    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < mlx_s->spriteNum; i++)
    {
      double spriteX = mlx_s->sprite[0]->x - ray->pos->x;
      double spriteY = mlx_s->sprite[0]->y - ray->pos->y;
      double invDet = 1.0 / (ray->plane->x * ray->dir->y - ray->dir->x * ray->plane->y); //required for correct matrix multiplication
      double transformX = invDet * (ray->dir->y * spriteX - ray->dir->x * spriteY);
      double transformY = invDet * (-ray->plane->y * spriteX + ray->plane->x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
      int spriteScreenX = (int)((mlx_s->width / 2) * (1 + transformX / transformY));
      int spriteHeight = abs((int)(mlx_s->height / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      int drawStartY = -spriteHeight / 2 + mlx_s->height / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + mlx_s->height / 2;
      if(drawEndY >= mlx_s->height) drawEndY = mlx_s->height - 1;

      int spriteWidth = abs((int)(mlx_s->height / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0)
        drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= mlx_s->width)
        drawEndX = mlx_s->width - 1;

      //loop through every vertical stripe of the sprite on screen
      for(stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;
        if(transformY > 0 && stripe > 0 && stripe < mlx_s->width && transformY < *mlx_s->zbuffer[stripe])
        {  
          
          for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
          {
           int d = (y) * 256 - mlx_s->height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
           int texY = ((d * 64) / spriteHeight) / 256;
           unsigned int color; //get current color from the texture
           mlx_pixel_get(mlx_s->tex->sprite, texX, texY, &color);
           if((color & 0x00FFFFFF) != 0) 
             my_mlx_pixel_put(mlx_s, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
          }
        }
      }
    }
  
}