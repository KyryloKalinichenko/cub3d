/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:22:54 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/08 17:36:26 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub_head.h"

static void	stripe_p(t_data *mlx_s, double *zbuffer, t_s *spr_s)
{
	int				texX;
	int				texY;
	int				y;
	int				d;
	unsigned int	color;

	while (spr_s->stripe < spr_s->drawEndX)
	{
		texX = (int )(256 * (spr_s->stripe - (-spr_s->spriteWidth / 2
						+ spr_s->spriteScreenX)) * 64
				/ spr_s->spriteWidth) / 256;
		//printf("%5d%5d%5d%5d\n", spr_s->transformY > 0, spr_s->stripe > 0, spr_s->stripe
		//	< mlx_s->width, spr_s->transformY < zbuffer[spr_s->stripe]);
		//printf("zb %5f transformY %5f stripe %5d\n", zbuffer[spr_s->stripe], spr_s->transformY, spr_s->stripe);
		if (spr_s->transformY > 0 && spr_s->stripe > 0 && spr_s->stripe
			< mlx_s->width && spr_s->transformY < zbuffer[spr_s->stripe])
		{
			y = spr_s->drawStartY - 1;
			while (++y < spr_s->drawEndY)
			{
				d = (y) * 256 - mlx_s->height * 128 + spr_s->spriteHeight * 128;
				texY = ((d * 64) / spr_s->spriteHeight) / 256;
				mlx_pixel_get(mlx_s->tex->sprite, texX, texY, &color);
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(mlx_s, spr_s->stripe, y, color);
			}
		}
		spr_s->stripe++;
	}
}

int	*sort_sp(t_data *mlx_s, t_ray *ray)
{
	int		i;
	int		*spOrder;
	double	*spDist;

	i = -1;
	spOrder = malloc(sizeof(int) * mlx_s->spriteNum);
	spDist = malloc(sizeof(double) * mlx_s->spriteNum);
	if (!spOrder || !spDist)
		error(1);
	while (++i < mlx_s->spriteNum)
	{
		spOrder[i] = i;
		spDist[i] = ((ray->pos->x - mlx_s->sprite[i]->x)
				* (ray->pos->x - mlx_s->sprite[i]->x)
				+ (ray->pos->y - mlx_s->sprite[i]->y)
				* (ray->pos->y - mlx_s->sprite[i]->y));
	}
	bubbleSort(spDist, spOrder, mlx_s->spriteNum);
	free(spDist);
	return (spOrder);
}

void	extra_sp(t_doub *db, t_data *mlx_s, t_ray *ray, t_s *spr_s)
{
	db->invDet = 1.0 / (ray->plane->x
			* ray->dir->y - ray->dir->x * ray->plane->y);
	db->transformX = db->invDet
		* (ray->dir->y * db->spriteX - ray->dir->x * db->spriteY);
	spr_s->transformY = db->invDet
		* (-ray->plane->y * db->spriteX + ray->plane->x * db->spriteY);
	spr_s->spriteScreenX = (int)((mlx_s->width / 2)
			* (1 + db->transformX / spr_s->transformY));
	spr_s->spriteHeight = abs((int)(mlx_s->height / (spr_s->transformY)));
	spr_s->drawStartY = -spr_s->spriteHeight / 2 + mlx_s->height / 2;
	spr_s->drawEndY = spr_s->spriteHeight / 2 + mlx_s->height / 2;
}

void	print_sprite(t_data *mlx_s, t_ray *ray, double *zbuffer)
{
	t_s		spr_s;
	int		i;
	int		*spOrder;
	t_doub	db;

	i = mlx_s->spriteNum;
	spOrder = sort_sp(mlx_s, ray);
	while (--i >= 0)
	{
		db.spriteX = mlx_s->sprite[spOrder[i]]->x - ray->pos->x;
		db.spriteY = mlx_s->sprite[spOrder[i]]->y - ray->pos->y;
		extra_sp(&db, mlx_s, ray, &spr_s);
		limits(&spr_s.drawStartY, &spr_s.drawEndY, mlx_s->height - 1);
		spr_s.spriteWidth = abs((int)(mlx_s->height / (spr_s.transformY)));
		spr_s.drawStartX = -spr_s.spriteWidth / 2 + spr_s.spriteScreenX;
		spr_s.drawEndX = spr_s.spriteWidth / 2 + spr_s.spriteScreenX;
		limits(&spr_s.drawStartX, &spr_s.drawEndX, mlx_s->width - 1);
		spr_s.stripe = spr_s.drawStartX;
		//printf("---%d-----\n", spr_s.stripe);
		stripe_p(mlx_s, zbuffer, &spr_s);
	}
	free(spOrder);
}

void	s_place(char **map, t_sprite **sprites)
{
	int			i;
	int			j;
	int			n;

	i = -1;
	j = -1;
	n = 0;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '2')
			{
				sprites[n] = put_s_place(i, j);
				n++;
			}
		}
		j = -1;
	}
}
