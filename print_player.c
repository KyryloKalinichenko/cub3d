#include "cub_head.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

static void	ft_draw_right_line(t_data *mlx_s, double delta)
{
	if (mlx_s->player.y == mlx_s->player.dy)
		delta = 0;
	while (mlx_s->player.x++ <= mlx_s->player.dx)
	{
		while (mlx_s->player.y != mlx_s->player.dy)
		{
			mlx_s->player.y += delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s->img, mlx_s->player.x, mlx_s->player.y, mlx_s->map_s->color);
	}
}

static void	ft_draw_left_line(t_data *mlx_s, double delta)
{
	if (mlx_s->player.y == mlx_s->player.dy)
		delta = 0;
	while (mlx_s->player.x-- >= mlx_s->player.dx)
	{
		while (mlx_s->player.y != mlx_s->player.dy)
		{
			mlx_s->player.y -= delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s->img, mlx_s->player.x, mlx_s->player.y, mlx_s->map_s->color);
    }
}

static void	ft_draw_down_line(t_data *mlx_s, double delta)
{
	my_mlx_pixel_put(mlx_s->img, mlx_s->player.x, mlx_s->player.y, mlx_s->map_s->color);
	if (mlx_s->player.x == mlx_s->player.dx)
		delta = 0;
	while (mlx_s->player.y-- >= mlx_s->player.dy)
	{
		while (mlx_s->player.x != mlx_s->player.dx)
		{
			mlx_s->player.x -= delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s->img, mlx_s->player.x, mlx_s->player.y, mlx_s->map_s->color);
	}
}

static void	ft_draw_up_line(t_data *mlx_s, double delta)
{
	if (mlx_s->player.x == mlx_s->player.dx)
		delta = 0;
	while (mlx_s->player.y++ <= mlx_s->player.dy)
	{
		while (mlx_s->player.x != mlx_s->player.dx)
		{
			mlx_s->player.x += delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s->img, mlx_s->player.x, mlx_s->player.y, mlx_s->map_s->color);
	}
}

void    print_v(t_data *mlx_s)
{
    double delta;

    delta = fabs(mlx_s->player.y - mlx_s->player.dy) - fabs(mlx_s->player.x - mlx_s->player.dx);
    printf("-------%f-------\n", delta);
	if (delta > 0)
	{
		delta = fabs(mlx_s->player.x - mlx_s->player.dx) / fabs(mlx_s->player.y - mlx_s->player.dy);
		if (mlx_s->player.y < mlx_s->player.dy)
			ft_draw_up_line(mlx_s, delta);
		else
			ft_draw_down_line(mlx_s, delta);
	}
	else
	{
		if (mlx_s->player.x < mlx_s->player.dy)
		{
			ft_draw_right_line(mlx_s, delta);
		}
		else if (mlx_s->player.x >= mlx_s->player.dx)
		{
			ft_draw_left_line(mlx_s, delta);
		}
	}

}

void    print_player(t_data *mlx_s)
{
    mlx_s->map_s->color = 0x0000FF00;
	printf("-------%f--%f-----\n", mlx_s->player.x, mlx_s->player.y);
    print_sq(mlx_s, mlx_s->player.x, mlx_s->player.y);
}