#ifndef CUB_HEAD_H
#define CUB_HEAD_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>

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
}					t_map;

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
    t_map        **map;
}               t_data;
/*
typedef struct  s_main {
    t_data      *mlx_s;
}               t_main;
*/
int					get_next_line(int fd, char **line);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
int                  init(/*t_main *main_str, */t_data *mlx);


#endif 