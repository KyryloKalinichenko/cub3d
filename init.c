#include "cub_head.h"
/*
** init_mlx make a connection to the display and create a window with all necessary variables by mlx_lib. 
**
*/

static void init_mlx(t_data *mlx_s)
{
    mlx_s->mlx = mlx_init();
    mlx_s->mlx_win = mlx_new_window(mlx_s->mlx, mlx_s->width, mlx_s->height, "Hello world!");
    mlx_s->img = mlx_new_image(mlx_s->mlx, mlx_s->width, mlx_s->height);
    mlx_s->addr = mlx_get_data_addr(mlx_s->img, &mlx_s->bits_per_pixel, &mlx_s->line_length,
                                 &mlx_s->endian);
   // mlx_s->player.x = START_X;
   // mlx_s->player.y = START_Y;
    mlx_s->player.x = mlx_s->map_s->width * 2;
	mlx_s->player.y = mlx_s->map_s->height * 2;
    mlx_s->player.a = FOV;
    mlx_s->player.dx = cos(mlx_s->player.a) * 5;
    mlx_s->player.dy = sin(mlx_s->player.a) * 5;
}

static int read_r(short fd, t_data *mlx_s)
{
    char *line;
    char **width_heiht;

    if (!(get_next_line(fd, &line)))
        return (1);
    width_heiht = ft_split(line, ' ');
    mlx_s->width = ft_atoi(width_heiht[0]);
    mlx_s->height = ft_atoi(width_heiht[1]);
    //printf("%d", mlx_s->width);
    //printf("%d", mlx_s->height);
    return (0);
}

static int height_count(char *file, t_data *mlx_s)
{
    short height;
    int i;
    int fd;
    char buff[BUFFER_SIZE + 1];
    
    height  = 0;
    fd = open(file, O_RDONLY);
    while ((i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[i] = '\0';
        if (ft_strchr(buff, 'R'))
        {
            read_r(fd, mlx_s);
            height--;
        }
		if (ft_strchr(buff, '\n'))
			height++;
	}
	return (height + 1);
}

static int parsing_map(char *file, t_data *mlx_s)
{
    int fd;
    int i;
    char **map;

    i = 0;
    fd = open(file, O_RDONLY);
    mlx_s->map_s->mapY = height_count(file, mlx_s);
    mlx_s->map_s->height = mlx_s->height / (mlx_s->map_s->mapY * 4);
    map = malloc(sizeof(char*) * mlx_s->map_s->mapY);
    mlx_s->map_s->map = map;
    while(get_next_line(fd, &map[i]) && ft_strchr(map[i], 'R'))
        free(map[i]);
    get_next_line(fd, &map[i]);
    mlx_s->map_s->mapX = ft_strlen(map[i]);
    mlx_s->map_s->mapS = mlx_s->map_s->mapX * mlx_s->map_s->mapY;
    mlx_s->map_s->width = mlx_s->width / (mlx_s->map_s->mapX * 4);
    while(get_next_line(fd, &map[++i]))
        ;
    map[i] = NULL;
    return (0);
}

int     init(t_data *mlx_s, char *file)
{
    t_map *map_s;
    t_ray   *ray = malloc(sizeof(t_ray));

    map_s = malloc(sizeof(t_map));
    mlx_s->map_s = map_s;
    parsing_map(file, mlx_s);
    init_mlx(mlx_s);
    print_map(mlx_s);
    //print_player(mlx_s);
    mlx_s->ray = ray;
    init_ray(ray, mlx_s);
    

    return (0);
}