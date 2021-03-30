#include "cub_head.h"

int main(int argc, char **argv)
{
    /*t_main main_str;*/
    t_data mlx_s;

    if (argc < 2)
        return(printf("Error\n"));
    init(/*&main_str,*/ &mlx_s, argv[1]);

   mlx_put_image_to_window(mlx_s.mlx, mlx_s.mlx_win, mlx_s.img, 0, 0);
   mlx_loop(mlx_s.mlx);
}