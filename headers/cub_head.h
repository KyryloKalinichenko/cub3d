/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_head.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:24:06 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/08 17:56:46 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_HEAD_H
# define CUB_HEAD_H

# define BUFFER_SIZE 10
# define PI 3.14159265359

# define TEXTWIDTH 64
# define TEXTHEIGHT 64

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "./mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include "val.h"

/*
** Structure for GNL.
*/
typedef struct s_list
{
	void	*con;
	char	*tmp;
}					t_list;

typedef struct s_doub
{
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
}					t_doub;

typedef struct s_point
{
	double	x;
	double	y;
	char	point;
}					t_point;

typedef struct s_on_map
{
	int	x;
	int	y;
}					t_on_map;

typedef struct s_put
{
	double			wallX;
	double			step;
	double			texPos;
	unsigned int	color;
}					t_put;
/*
** The structure to store the map, its width and height.
*/

typedef struct s_map
{
	int		height;
	int		width;
	char	**map;
	int		color;
	short	mapX;
	short	mapY;
	short	mapS;
	t_point	*start;
}					t_map;

/*
** The structure to print a square and save its
** width and height (calculated up to proportion of the map).
*/

typedef struct s_sq
{
	short	height;
	short	width;
	int		x;
	int		y;
}					t_sq;

/*
** The structure to print a vector and save its coordinates.
*/

typedef struct s_line
{
	double	x;
	double	y;
	double	dx;
	double	dy;
}				t_line;

/*
** The structure to store data for rays.
*/

typedef struct s_ray
{
	double		camera_x;
	t_point		*ray_dir;
	t_point		*dir;
	t_on_map	*on_map;
	t_on_map	*step;
	t_point		*side_dist;
	t_point		*delta_dist;
	t_point		*plane;
	t_point		*pos;
	int			side;
	int			hit;
}					t_ray;

/*
** The structure to print the player and save its coordinates.
*/

typedef struct s_pl
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	double	a;
}				t_pl;

typedef struct s_floor
{
	double	floorX;
	double	floorY;
	double	floorStepY;
	double	floorStepX;
	int		y;
}				t_floor;

typedef struct s_r_dir
{
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	int		p;
	float	posZ;
	float	rowDistance;
}				t_r_dir;

typedef struct s_cel
{
	int				cellX;
	int				cellY;
	int				tx;
	int				ty;
	int				x;
}				t_cel;

typedef struct s_wall
{
	double	perpWallDist;
	double	lineHeight;
	int		drawEnd;
	int		drawStart;
}				t_wall;

/*
** The structure to save all necessary data for texture 
**
*/

typedef struct s_tex
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_tex;

typedef struct s_sides
{
	t_tex	*no_side;
	t_tex	*so_side;
	t_tex	*we_side;
	t_tex	*ea_side;
	t_tex	*sprite;
}				t_sides;

typedef struct s_sprite
{
	double	x;
	double	y;
	t_tex	*tex;
}				t_sprite;

typedef struct s_s
{
	double	transformY;
	int		spriteScreenX;
	int		spriteHeight;
	int		drawStartY;
	int		drawEndY;
	int		spriteWidth;
	int		drawStartX;
	int		drawEndX;
	int		stripe;
}				t_s;
/*
** The main structure to store all necessary data for displaying an image.
*/

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	t_sides		*tex;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
	t_map		*map_s;
	t_pl		player;
	t_ray		*ray;
	t_ray		ray_s;
	char		**side[8];
	int			cel;
	int			floor;
	double		*zbuffer;
	short		spriteNum;
	t_sprite	**sprite;
	short		fl;
}					t_data;

int					get_next_line(int fd, char **line);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
int					init(t_data *mlx, char *file);
char				**ft_split(char const *s, char c);
int					ft_atoi(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int					ft_isdigit(int c);

int					main(int argc, char **argv);

void				print_map(t_data *mlx_s);
void				print_player(t_data *mlx_s);
int					create_trgb(int t, int r, int g, int b);
void				print_sq(t_data *mlx_s, int x, int y, int color);
void				print_v(t_data *mlx_s, t_line vector);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);

void				ray_fun(t_data *mlx_s, t_ray *ray);
void				init_ray(t_ray *ray, t_point *start);
void				turn_l(t_ray *ray);
void				turn_r(t_ray *ray);
void				print_ver_line(int drawStart, int drawEnd,
						int x, t_data *mlx_s);
void				print_back(int drawStart, int drawEnd,
						int x, t_data *mlx_s);

void				malloc_error(void);
int					just_exit(void);
void				no_file(void);
void				check_map(char **map, int last, t_point *start);
void				map_err(void);
t_tex				*init_text(t_data *mlx_s, char *path, t_tex *tex);
void				put_text(int i, t_data *mlx_s, t_wall *wall_s, t_tex *tex);
void				mlx_pixel_get(t_tex *data, int x,
						int y, unsigned int *color);
void				textures(t_data *mlx_s, t_sides *tex);
int					ft_strcmp(const char *s1, const char *s2);
void				print_floor(t_data *mlx_s, t_ray *ray);
void				print_sprite(t_data *mlx_s, t_ray *ray, double *zbuffer);
int					s_count(char **map);
void				s_place(char **map, t_sprite **sprites);
void				save_image(t_data *mlx_s);
void				mlx_pixel_get_2(t_data *data, int x, int y, int *color);
void				tab_free(char **tab);
int					height_count(char *file, t_data *mlx_s);
void				read_r(char **tab, t_data *mlx_s);
int					line_check(char *line);
int					char_check(char c);
void				wrong_flag(void);

void				bubbleSort(double *arr, int *ord, int n);
void				parsing_map(char *file, t_data *mlx_s);
void				ft_bzero(void *s, size_t n);
int					ft_get_r(int m);
int					ft_get_g(int m);
int					ft_get_b(int m);
void				limits(int *start, int *end, int limit);
void				textures(t_data *mlx_s, t_sides *tex);
void				print_sprite(t_data *mlx_s, t_ray *ray, double *zbuffer);
t_sprite			*put_s_place(int i, int j);
void				turn_start(t_ray *ray, char c);
void				turn_start2(t_ray *ray, char c);
void				load(t_ray *ray, t_point *start);
void				back_forth(t_data *mlx_s, int keycode);
void				left_right(t_data *mlx_s, int keycode, char **map);
int	ft_iswhitespace(char c);
int	ft_isstrwhitespace(char c);
int	ft_isotherwhitespace(char c);
void	error(int code);

#endif 
