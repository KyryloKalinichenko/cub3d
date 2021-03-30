#include "cub_head.h"
#include <fcntl.h>

static void init_mlx(t_data *mlx_s)
{
    mlx_s->mlx = mlx_init();
    mlx_s->mlx_win = mlx_new_window(mlx_s->mlx, 1920, 1080, "Hello world!");
    mlx_s->img = mlx_new_image(mlx_s->mlx, 1920, 1080);
    mlx_s->addr = mlx_get_data_addr(mlx_s->img, &mlx_s->bits_per_pixel, &mlx_s->line_length,
                                 &mlx_s->endian);
}

static int rear_r(short fd, t_map *map_s)
{
    char *line;
    char **width_heiht;

    if (!(get_next_line(fd, &line))
        return (1);
    width_heiht = ft_split(line, ' ');
    map_s->width = ft_atoi(width_heiht[0]);
    map_s->width = ft_atoi(width_heiht[1]);

}


static int height_count(short fd, t_map *map_s)
{
    short height;
    int i;
    char buff[BUFFER_SIZE + 1];
    
    height  = 0;
	while ((i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[i] = '\0';
        if (ft_strchr(buff, 'R'))
        {
            read_r(fd, map_s);
        }
		else if (ft_strchr(buff, '\n'))
			height++;
	}
	return (height + 1);
}

static int parsing_map(char *file, t_map *map_s)
{
    short fd;
    char **map;

    fd = open(file, O_RDONLY);
    map = map_s->map;
    while (get_next_line(fd, map))
    {

    }
}

int     init(/*t_main *main_str, */t_data *mlx_s, char *file)
{
    static t_map map_s;

    mlx_s->map = &map_s; 
    parsing_map(file, &map_s);
    init_mlx(mlx_s);

    return (0);
}