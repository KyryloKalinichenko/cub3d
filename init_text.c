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
  while (++i < 6)
  {
    if(!ft_strcmp(mlx_s->side[i][0], "NO"))
    {
      
      tex->no_side = init_text(mlx_s, mlx_s->side[i][1], tex->no_side);
    }
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
  }
    //printf("too bad %d\n", tex->no_side->bits_per_pixel);
}

t_tex *init_text(t_data *mlx_s, char *path, t_tex *tex)
{
    int width = mlx_s->width;
    int height = mlx_s->height;
     
    //printf("width %i, height %i \n", width, height);
    
    //img = mlx_new_image(mlx_s->mlx, mlx_s->width, mlx_s->height);
    tex = malloc(sizeof(t_tex));
    if (!tex)
      malloc_error();
    //printf("---------%s------%d-----\n", path, tex == NULL);
    if (!(tex->img = mlx_xpm_file_to_image(mlx_s->mlx, path, &width, &height)))
      malloc_error();
    if (!(tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel, &tex->line_length,
                                 &tex->endian)))
                                 malloc_error();
    return(tex);
}

void    put_text(int drawStart, int drawEnd, int i, t_data *mlx_s, double lineHeight, double perpWallDist, t_tex *tex)
{
    //char texNum = mlx_s->map_s->map[(int)mlx_s->ray->on_map->x][(int)mlx_s->ray->on_map->y]; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
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
      // Starting texture coordinate
      double texPos = (drawStart - mlx_s->height / 2 + lineHeight / 2) * step;
      int texY;
      unsigned int color = 0;
      int y = drawStart;
      while(y < (int)drawEnd)
      {
        texY = (int)texPos & (64 - 1);
        texPos += step;
       //printf(" xt - %i\n yt - %i\n", texX, texY);
       //printf("%p \n", mlx_s->tex->no_side);
      //printf("-----------------------\n");
        mlx_pixel_get(tex, texX, texY, &color);
      //printf("-----------------------\n");
        //printf("color - %i\n", color);
        my_mlx_pixel_put(mlx_s, i, y, color);
          //printf("wow\n");
          y++;
      }
}