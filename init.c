#include "cub_head.h"
/*
** init_mlx make a connection to the display and create a window with all necessary variables by mlx_lib. 
**
*/

static void init_mlx(t_data *mlx_s)
{
    mlx_s->mlx = mlx_init();
    mlx_s->mlx_win = mlx_new_window(mlx_s->mlx, mlx_s->width, mlx_s->height, "The cub is here!");
    mlx_s->img = mlx_new_image(mlx_s->mlx, mlx_s->width, mlx_s->height);
    mlx_s->addr = mlx_get_data_addr(mlx_s->img, &mlx_s->bits_per_pixel, &mlx_s->line_length,
                                 &mlx_s->endian);
    mlx_s->up = 0;
    mlx_s->zbuffer = malloc(sizeof(double*) * mlx_s->width);
    mlx_s->spriteNum = s_count(mlx_s->map_s->map);
    mlx_s->sprite = malloc(sizeof(t_sprite*));
    mlx_s->sprite[0] = s_place(mlx_s->map_s->map/*, *mlx_s->sprite*/);
}

/*
** Read resolution and conver it into two int. 
**
*/

static int read_r(char **tab, t_data *mlx_s)
{
    int i;

    i = -1;
    while(tab[++i])
    {
        if (i == 1)
            mlx_s->width = ft_atoi(tab[i]);
        else if (i == 2)
            mlx_s->height = ft_atoi(tab[2]);
        free(tab[i]);
    }
    return (0);
}

/*
** Count height of the map. Return int. 
**
*/

int			ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static int char_check(char c)
{
    char *here;
    int i;

    here = "012WSEN ";
    i = -1;
    while(here[++i])
    {
        if (here[i] == c)
            return (1);
    }
    return (0);
}

static int line_check(char *line)
{
    int i;

    i = -1;
    while (line[++i])
    {
        if (!char_check(line[i]))
            return (0);
    }
    return (1);
}

static int height_count(char *file, t_data *mlx_s)
{
    short height;
    int fd;
    char *buff;
    char **tab;
    int i;
    
    height  = 1;
    fd = open(file, O_RDONLY);
    i = -1;
    if (!fd)
        malloc_error();
    while (get_next_line(fd, &buff) >= 0)
	{
        if (!ft_strcmp("", buff))
            continue ;
        if (!(tab = ft_split(buff, ' ')))
            malloc_error();
        if (!ft_strcmp(tab[0], "R") && tab[1])
            read_r(tab, mlx_s);
        else if (!ft_strcmp(tab[0], "NO") && tab[1])
            mlx_s->side[++i] = tab;
        else if (!ft_strcmp(tab[0], "SO") && tab[1])
            mlx_s->side[++i] = tab;
        else if (!ft_strcmp(tab[0], "WE") && tab[1])
            mlx_s->side[++i] = tab;
        else if (!ft_strcmp(tab[0], "EA") && tab[1])
            mlx_s->side[++i] = tab;
        else if (!ft_strcmp(tab[0], "S") && tab[1])
            mlx_s->side[++i] = tab;
        else if (!ft_strcmp(tab[0], "F") && tab[1])
            mlx_s->side[++i] = tab;
        else if (!ft_strcmp(tab[0], "C") && tab[1])
            mlx_s->side[++i] = tab;
        else if (!ft_strcmp(tab[0], "S") && tab[1])
            mlx_s->side[++i] = tab;
        else
            break ;
        free(buff);
	}
    while (get_next_line(fd, &buff) > 0)
    {
        if (!line_check(buff))
            map_err();
        height++;
        free(buff);
    }
	return (height + 1);
}

/*
** The main parsing function. 
**
*/

static int parsing_map(char *file, t_data *mlx_s)
{
    int fd;
    int i;
    char **map;

    i = 0;
    fd = open(file, O_RDONLY);
    if (!fd)
        no_file();
    mlx_s->map_s->mapY = (height_count(file, mlx_s));
    mlx_s->map_s->height = mlx_s->height / (mlx_s->map_s->mapY * MINIMAP_S);
    map = malloc(sizeof(char*) * mlx_s->map_s->mapY);
    if (!map)
        malloc_error();
    mlx_s->map_s->map = map;
    while(1)
    {
        get_next_line(fd, &map[i]);
        if (line_check(map[i]) && ft_strcmp(map[i], ""))
            break ;
        free(map[i]);
    }
    mlx_s->map_s->mapX = ft_strlen(map[i]);
    while(get_next_line(fd, &map[++i]))
    {
        if (mlx_s->map_s->mapX < (int)ft_strlen(map[i]))
           mlx_s->map_s->mapX = ft_strlen(map[i]);
    }
    map[i] = NULL;
    mlx_s->map_s->mapS = mlx_s->map_s->mapX * mlx_s->map_s->mapY;
    mlx_s->map_s->width = mlx_s->width / (mlx_s->map_s->mapX * 4);
    return (0);
}

int     init(t_data *mlx_s, char *file)
{
    t_map *map_s;
    t_ray   *ray;

    ray = malloc(sizeof(t_ray));
    map_s = malloc(sizeof(t_map));
    mlx_s->tex = malloc(sizeof(t_sides));
    if (!map_s || !ray || !mlx_s->tex) 
        malloc_error();
    mlx_s->map_s = map_s;
    parsing_map(file, mlx_s);
    check_map(mlx_s->map_s->map, mlx_s->map_s->mapY);
    init_mlx(mlx_s);
    mlx_s->ray = ray;
    textures(mlx_s, mlx_s->tex);
    init_ray(ray);
    return (0);
}