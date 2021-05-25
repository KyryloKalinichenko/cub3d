/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:03:38 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/05 11:19:26 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

static void	init_header(int fd, int size)
{
	unsigned char	header[14];

	ft_bzero(header, 14);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(size + 14 + 40);
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)(14 + 40);
	write(fd, header, sizeof(header));
}

static void	init_infoheader(int fd, int height, int width)
{
	char	info_header[40];

	ft_bzero(info_header, 40);
	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(width);
	info_header[5] = (unsigned char)(width >> 8);
	info_header[6] = (unsigned char)(width >> 16);
	info_header[7] = (unsigned char)(width >> 24);
	info_header[8] = (unsigned char)(height);
	info_header[9] = (unsigned char)(height >> 8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(24);
	write(fd, info_header, sizeof(info_header));
}

static void	put_color(int fd, int color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	b = (unsigned char)(ft_get_b(color));
	g = (unsigned char)(ft_get_g(color));
	r = (unsigned char)(ft_get_r(color));
	write(fd, &b, sizeof(b));
	write(fd, &g, sizeof(g));
	write(fd, &r, sizeof(r));
}

static void	cond(t_data *mlx_s, int i, int fd)
{
	int	j;
	int	color;

	if (mlx_s->width % 4)
		j = -1;
	else
		j = 0;
	while (++j <= mlx_s->width)
	{
		mlx_pixel_get_2(mlx_s, j, i, &color);
		put_color(fd, color);
	}
}

void	save_image(t_data *mlx_s)
{
	int	fd;
	int	i;
	int	mod;

	i = mlx_s->height;
	if ((mlx_s->width * 3) % 4)
		mod = (mlx_s->width * 3) + (4 - ((mlx_s->width * 3) % 4));
	else
		mod = mlx_s->width * 3;
	fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, 77777);
	if (fd == -1)
		error(3);
	init_header(fd, ((mlx_s->width * 3)
			+ ((4 - (mlx_s->width * 3) % 4) % 4) * mlx_s->height));
	init_infoheader(fd, mlx_s->height, mlx_s->width);
	while (--i > 0)
		cond(mlx_s, i, fd);
	if (close(fd) < 0)
		error(4);
	else
		printf("BMP file saved!\n");
	exit(EXIT_SUCCESS);
}
