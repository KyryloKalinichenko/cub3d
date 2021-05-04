#ifndef CUB_HEAD_H
# define CUB_HEAD_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define DOWN 125
# define TLEFT 123
# define TRIGHT 124
# define FORTH 13
# define BACK 1
# define LEFT 0
# define RIGHT 2

# define NO 1
# define SO 2
# define WE 4
# define EA 8
# define C 16
# define F 32
# define S 64

# define ESC 53

# define PI 3.14159265359
# define FOV (PI / 4)
# define SPEED 0.2
# define MSPEED 0.1
# define MINIMAP_S 5

# define TEXTWIDTH 64
# define TEXTHEIGHT 64

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "./mlx.h"
# include <unistd.h>
# include <fcntl.h>

/*
** Structure for GNL.
*/
typedef struct s_list
{
	void	*con;
	char	*tmp;
}					t_list;

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
	double		**zbuffer;
	short		spriteNum;
	t_sprite	**sprite;
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
void				put_text(int drawStart, int drawEnd, int i, t_data *mlx_s,
						double lineHeight, double perpWallDists, t_tex *tex);
void				mlx_pixel_get(t_tex *data, int x,
						int y, unsigned int *color);
void				textures(t_data *mlx_s, t_sides *tex);
int					ft_strcmp(const char *s1, const char *s2);
void				print_floor(t_data *mlx_s, t_ray *ray);
void				print_sprite(t_data *mlx_s, t_ray *ray);
int					s_count(char **map);
t_sprite			*s_place(char **map);
void				save_image(t_data *mlx_s);
void				mlx_pixel_get_2(t_data *data, int x, int y, int *color);
void				tab_free(char **tab);
int					height_count(char *file, t_data *mlx_s);
int					read_r(char **tab, t_data *mlx_s);
int					line_check(char *line);
int					char_check(char c);
void				wrong_flag(void);

#endif 
