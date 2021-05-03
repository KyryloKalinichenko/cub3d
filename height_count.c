#include "cub_head.h"

static void skip(t_data *mlx_s, int fd)
{
    int i;
    char *buff;
    char **tab;

    i = -1;
    while (get_next_line(fd, &buff) > 0)
	{
       // printf("------------\n");
        if (!ft_strcmp("", buff))
        {
            free(buff);
            continue ;
        }
        if (line_check(buff))
            break ;
        if (!(tab = ft_split(buff, ' ')))
            malloc_error();
        if (!ft_strcmp(tab[0], "R") && tab[1] && tab[2])
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
        /*else
        {
            free(buff);
            free(tab[0]);
            free(tab[1]);
            free(tab);
            break ;
        }*/
        //free(tab);
        free(buff);
	}
    free(buff);
}

int height_count(char *file, t_data *mlx_s)
{
    short height;
    int fd;
    char *buff;
    
    height  = 1;
    fd = open(file, O_RDONLY);
    if (!fd)
        malloc_error();
    skip(mlx_s, fd);
    //free(buff);
    mlx_s->side[7] = NULL;
    //printf("----*****------\n");
    int k;
    while (1)
    {
        k = get_next_line(fd, &buff);
       // printf("%s\n", buff);
        //map_err();
        if (!line_check(buff))
            map_err();
       // printf("%d\n", height++);
       height++;
       free(buff);
       if (k == 0)
        break ;
    }
   // getchar();
    //printf("%d\n", height);

	return (height + 1);
}
