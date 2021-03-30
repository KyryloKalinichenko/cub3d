#include "cub_head.h"

int main(int argc, char **argv)
{
    /*t_main main_str;*/
    t_data mlx_s;
    //mlx_s = malloc(sizeof(t_data));
    if (argc == 1)
        return(printf("Error\n"));
    init(&mlx_s, argv[1]);
    printf("-----%i-----", mlx_s.height);
    return (0);
    //free(mlx_s);
    mlx_put_image_to_window(mlx_s.mlx, mlx_s.mlx_win, mlx_s.img, 0, 0);
    mlx_loop(mlx_s.mlx);
}