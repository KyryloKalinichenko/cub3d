/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 10:33:01 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/08 16:20:43 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

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
