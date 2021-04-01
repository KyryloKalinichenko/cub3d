#include "cub_head.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

static void	ft_draw_right_line(t_data *mlx_s, double delta)
{
	if (mlx_s->line.y == mlx_s->line.dy)
		delta = 0;
	while (mlx_s->line.x++ <= mlx_s->line.dx)
	{
		while (mlx_s->line.y != mlx_s->line.dy)
		{
			mlx_s->line.y += delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, mlx_s->line.x, mlx_s->line.y, mlx_s->map_s->color);
	}
}

static void	ft_draw_left_line(t_data *mlx_s, double delta)
{
	if (mlx_s->line.y == mlx_s->line.dy)
		delta = 0;
	while (mlx_s->line.x-- >= mlx_s->line.dx)
	{
		while (mlx_s->line.y != mlx_s->line.dy)
		{
			mlx_s->line.y -= delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, mlx_s->line.x, mlx_s->line.y, mlx_s->map_s->color);
    }
}

static void	ft_draw_down_line(t_data *mlx_s, double delta)
{
	my_mlx_pixel_put(mlx_s, mlx_s->line.x, mlx_s->line.y, mlx_s->map_s->color);
	if (mlx_s->line.x == mlx_s->line.dx)
		delta = 0;
	while (mlx_s->line.y-- >= mlx_s->line.dy)
	{
		while (mlx_s->line.x != mlx_s->line.dx)
		{
			mlx_s->line.x -= delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, mlx_s->line.x, mlx_s->line.y, mlx_s->map_s->color);
	}
}

static void	ft_draw_up_line(t_data *mlx_s, double delta)
{
	if (mlx_s->line.x == mlx_s->line.dx)
		delta = 0;
	while (mlx_s->line.y++ <= mlx_s->line.dy)
	{
		while (mlx_s->line.x != mlx_s->line.dx)
		{
			mlx_s->line.x += delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, mlx_s->line.x, mlx_s->line.y, mlx_s->map_s->color);
	}
}

void    print_v(t_data *mlx_s)
{
    double delta;
	
    delta = fabs(mlx_s->line.y - mlx_s->line.dy) - fabs(mlx_s->line.x - mlx_s->line.dx);
	//printf("-------%i--%f-----\n", mlx_s->line.dx, delta);
	my_mlx_pixel_put(mlx_s, mlx_s->line.x, mlx_s->line.y, mlx_s->map_s->color);
	if (delta > 0)
	{
		delta = (mlx_s->line.x - mlx_s->line.dx) / (mlx_s->line.y - mlx_s->line.dy);
		if (mlx_s->line.y < mlx_s->line.dy)
			ft_draw_up_line(mlx_s, delta);
		else
			ft_draw_down_line(mlx_s, delta);
	}
	else
	{
		delta = (mlx_s->line.y - mlx_s->line.dy) / (mlx_s->line.x - mlx_s->line.dx);
		if (mlx_s->line.x < mlx_s->line.dx)
			ft_draw_right_line(mlx_s, delta);
		else if (mlx_s->line.x >= mlx_s->line.dx)
			ft_draw_left_line(mlx_s, delta);
	}
}

void    print_player(t_data *mlx_s)
{
    mlx_s->map_s->color = 0x0000FF00;
	//printf("-------%i--%i-----\n", mlx_s->map_s->width, mlx_s->map_s->height);
    print_sq(mlx_s, mlx_s->player.x, mlx_s->player.y);
	mlx_s->line.x = mlx_s->player.x + (mlx_s->map_s->width / 2);
	mlx_s->line.y = mlx_s->player.y + (mlx_s->map_s->height / 2); 
	mlx_s->line.dx = mlx_s->line.x + (mlx_s->player.dx * 10);
	mlx_s->line.dy = mlx_s->line.y + (mlx_s->player.dy * 10);
	print_v(mlx_s);
	ray_fun(mlx_s);
}