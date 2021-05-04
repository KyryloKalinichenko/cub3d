/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 10:33:01 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/04 16:47:10 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_head.h"

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

t_tex	*init_text(t_data *mlx_s, char *path, t_tex *tex)
{
	int	width;
	int	height;

	height = mlx_s->height;
	width = mlx_s->width;
	tex = malloc(sizeof(t_tex));
	if (!tex)
		malloc_error();
	if (!(tex->img
			= mlx_xpm_file_to_image(mlx_s->mlx, path, &width, &height)))
		malloc_error();
	if (!(tex->addr
			= mlx_get_data_addr(tex->img,
				&tex->bits_per_pixel, &tex->line_length, &tex->endian)))
		malloc_error();
	return (tex);
}

static void	wall_x(t_data *mlx_s, t_put *put_s, t_wall *wall_s)
{
	if (mlx_s->ray->side == 0)
		put_s->wallX = mlx_s->ray->pos->y
			+ wall_s->perpWallDist * mlx_s->ray->ray_dir->y;
	else
		put_s->wallX = mlx_s->ray->pos->x
			+ wall_s->perpWallDist * mlx_s->ray->ray_dir->x;
	put_s->wallX -= floor(put_s->wallX);
}

void	put_text(int i, t_data *mlx_s, t_wall *wall_s, t_tex *tex)
{
	t_on_map	tex_s;
	t_put		put_s;
	int			y;

	wall_x(mlx_s, &put_s, wall_s);
	tex_s.x = (int)(put_s.wallX * (double)(64));
	if (mlx_s->ray->side == 0 && mlx_s->ray->ray_dir->x > 0)
		tex_s.x = 64 - tex_s.x - 1;
	if (mlx_s->ray->side == 1 && mlx_s->ray->ray_dir->y < 0)
		tex_s.x = 64 - tex_s.x - 1;
	put_s.step = 1.0 * 64 / wall_s->lineHeight;
	put_s.texPos = (wall_s->drawStart - mlx_s->height
			/ 2 + wall_s->lineHeight / 2) * put_s.step;
	put_s.color = 0;
	y = wall_s->drawStart - 1;
	while (++y < (int)wall_s->drawEnd)
	{
		tex_s.y = (int)put_s.texPos & (64 - 1);
		put_s.texPos += put_s.step;
		mlx_pixel_get(tex, tex_s.x, tex_s.y, &put_s.color);
		my_mlx_pixel_put(mlx_s, i, y, put_s.color);
	}
}

void	print_sprite(t_data *mlx_s, t_ray *ray)
{
	int	stripe;
	int i;
    //sort sprites from far to close
    //t_sprite mlx_s->sprite[mlx_s->spriteNum];
	int spriteOrder[mlx_s->spriteNum];
	double spriteDistance[mlx_s->spriteNum];
	
	i = -1;
	while (++i < mlx_s->spriteNum)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((ray->pos->x - mlx_s->sprite[i]->x) * (ray->pos->x - mlx_s->sprite[i]->x) + (ray->pos->y - mlx_s->sprite[i]->y) * (ray->pos->y - mlx_s->sprite[i]->y)); //sqrt not taken, unneeded
	}
	//sortSprites(spriteOrder, spriteDistance, numSprites);
	////after sorting the sprites, do the projection and draw them
	i = -1;
	while (++i < mlx_s->spriteNum)
	{
		double spriteX = mlx_s->sprite[0]->x - ray->pos->x;
		double spriteY = mlx_s->sprite[0]->y - ray->pos->y;
		double invDet = 1.0 / (ray->plane->x * ray->dir->y - ray->dir->x * ray->plane->y); //required for correct matrix multiplication
		double transformX = invDet * (ray->dir->y * spriteX - ray->dir->x * spriteY);
		double transformY = invDet * (-ray->plane->y * spriteX + ray->plane->x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
		int spriteScreenX = (int)((mlx_s->width / 2) * (1 + transformX / transformY));
		int spriteHeight = abs((int)(mlx_s->height / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		int drawStartY = -spriteHeight / 2 + mlx_s->height / 2;
		
		if (drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + mlx_s->height / 2;
		if (drawEndY >= mlx_s->height) drawEndY = mlx_s->height - 1;
		int spriteWidth = abs((int)(mlx_s->height / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= mlx_s->width)
			drawEndX = mlx_s->width - 1;

      //loop through every vertical stripe of the sprite on screen
		stripe = drawStartX - 1;
		while (++stripe < drawEndX)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < mlx_s->width && transformY < *mlx_s->zbuffer[stripe])
			{
          		int y = drawStartY - 1;
				while (++y < drawEndY) //for every pixel of the current stripe
				{
					int d = (y) * 256 - mlx_s->height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * 64) / spriteHeight) / 256;
					unsigned int color; //get current color from the texture
					mlx_pixel_get(mlx_s->tex->sprite, texX, texY, &color);
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(mlx_s, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
				}
			}
		}
	}
}
