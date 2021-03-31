#ifndef CUB_HEAD_H
#define CUB_HEAD_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#define FORTH 126
#define BACK 125
#define LEFT 123
#define RIGHT 124
#define START_X 200
#define START_Y 200
#define PI 3.14159

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct		s_list
{
	void	*con;
	char	*tmp;
}					t_list;

typedef struct		s_map
{
	short       height;
    short       width;
    char        **map;
    int         color;
}					t_map;

typedef struct		s_sq
{
	short       height;
    short       width;
    int         x;
    int         y;
}					t_sq;


typedef struct  s_pl {
    double         x;
    double         y;
    double         dx;
    double         dy;
    double      a;
}               t_pl;

typedef struct  s_data {
    void        *mlx;
    void        *mlx_win;
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    short       height;
    short       width;
    t_map       *map_s;
    t_pl        player;
}               t_data;

int					get_next_line(int fd, char **line);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
int                  init(t_data *mlx, char *file);
char				**ft_split(char const *s, char c);
int					ft_atoi(const char *str);
size_t	            ft_strlcpy(char *dest, const char *src, size_t size);
int		            ft_isdigit(int c);
int                 main(int argc, char **argv);
void                print_map(t_data *mlx_s);
void                print_player(t_data *mlx_s);
int		            create_trgb(int t, int r, int g, int b);
void                print_sq(t_data *mlx_s, int x, int y);
void                print_v(t_data *mlx_s);
void                my_mlx_pixel_put(t_data *data, int x, int y, int color);


#endif 