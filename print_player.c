#include "cub_head.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

static void	ft_draw_right_line(t_data *mlx_s, double delta, t_line vector)
{
	if (vector.y == vector.dy)
		delta = 0;
	while (vector.x++ <= vector.dx)
	{
		while (vector.y != vector.dy)
		{
			vector.y += delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
	}
}

static void	ft_draw_left_line(t_data *mlx_s, double delta, t_line vector)
{
	if (vector.y == vector.dy)
		delta = 0;
	while (vector.x-- >= vector.dx)
	{
		while (vector.y != vector.dy)
		{
			vector.y -= delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
    }
}

static void	ft_draw_down_line(t_data *mlx_s, double delta, t_line vector)
{
	my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
	if (vector.x == vector.dx)
		delta = 0;
	while (vector.y-- >= vector.dy)
	{
		while (vector.x != vector.dx)
		{
			vector.x -= delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
	}
}

static void	ft_draw_up_line(t_data *mlx_s, double delta, t_line vector)
{
	if (vector.x == vector.dx)
		delta = 0;
	while (vector.y++ <= vector.dy)
	{
		while (vector.x != vector.dx)
		{
			vector.x += delta;
			break ;
		}
		my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
	}
}

void    print_v(t_data *mlx_s, t_line vector)
{
    double delta;
	
    delta = fabs(vector.y - vector.dy) - fabs(vector.x - vector.dx);
	//printf("-------%i--%f-----\n", vector.dx, delta);
	//my_mlx_pixel_put(mlx_s, vector.x, vector.y, mlx_s->map_s->color);
	if (delta > 0)
	{
		delta = (vector.x - vector.dx) / (vector.y - vector.dy);
		if (vector.y < vector.dy)
			ft_draw_up_line(mlx_s, delta, vector);
		else
			ft_draw_down_line(mlx_s, delta, vector);
	}
	else
	{
		delta = (vector.y - vector.dy) / (vector.x - vector.dx);
		if (vector.x < vector.dx)
			ft_draw_right_line(mlx_s, delta, vector);
		else if (vector.x >= vector.dx)
			ft_draw_left_line(mlx_s, delta, vector);
	}
}

void    print_player(t_data *mlx_s)
{
	t_line vector;

	
    mlx_s->map_s->color = 0x0000FF00;
	
	
	ray_fun(mlx_s, mlx_s->ray);
	print_map(mlx_s);
	//printf("-------%f--%f-----\n", mlx_s->ray->pos->y, mlx_s->ray->pos->y);
	print_sq(mlx_s, (mlx_s->ray->pos->x * mlx_s->map_s->width), (mlx_s->ray->pos->y * mlx_s->map_s->height));
	vector.x = mlx_s->ray->pos->x * mlx_s->map_s->width + mlx_s->map_s->width / 2;
	vector.y = mlx_s->ray->pos->y * mlx_s->map_s->height + mlx_s->map_s->height / 2; 
	vector.dx = vector.x + (mlx_s->ray->dir->x * 10);
	vector.dy = vector.y + (mlx_s->ray->dir->y * 10);
	//printf("-------%f--%f-----\n", vector.x, vector.y);
	print_v(mlx_s, vector);
	//ray_fun(mlx_s, mlx_s->ray);
	//mlx_s->ray->pos->x = mlx_s->player.x /*+ (mlx_s->map_s->width / 2)*/;
    //mlx_s->ray->pos->y = mlx_s->player.y /*+ (mlx_s->map_s->height / 2)*/;
	
	//ray_fun(mlx_s, mlx_s->ray);
}