#include "cub_head.h"
//#include <stdio.h>

static void	ft_bzero(void *s, size_t n)
{
	unsigned char *n_s;

	n_s = s;
	while (n)
	{
		*n_s = 0;
		n_s++;
		n--;
	}
}

static void    init_header(int fd, int size)
{
    unsigned char header[14];

    ft_bzero(header, 14);
    header[0] = (unsigned char)('B');
    header[1] = (unsigned char)('M');
    header[2] = (unsigned char)(size + 14 + 40);
    header[3] = (unsigned char)(size >> 8);
    header[4] = (unsigned char)(size >> 16);
    header[5] = (unsigned char)(size >> 24);
    header[10] = (unsigned char)(14 + 40);
    write(fd, header, sizeof(header));
}

static void init_infoheader(fd, height, width)
{
    char info_header[40];

    ft_bzero(info_header, 40);
    info_header[0] = (unsigned char)(40);
    info_header[4] = (unsigned char)(width);
    info_header[5] = (unsigned char)(width >> 8);
    info_header[6] = (unsigned char)(width >> 16);
    info_header[7] = (unsigned char)(width >> 24);
    info_header[8] = (unsigned char)(height);
    info_header[9] = (unsigned char)(height >> 8);
    info_header[10] = (unsigned char)(height >> 16);
    info_header[11] = (unsigned char)(height >> 24);
    info_header[12] = (unsigned char)(1);
    info_header[14] = (unsigned char)(24);
    write(fd, info_header, sizeof(info_header));
}

int		ft_get_i(int m)
{
	return (0x00000000 | ((m >> 24) & 0xFFFFFFFF));
}

int		ft_get_r(int m)
{
	return (0x00000000 | ((m >> 16) & 0xFFFFFFFF));
}

int		ft_get_g(int m)
{
	return (0x00000000 | ((m >> 8) & 0xFFFFFFFF));
}

int		ft_get_b(int m)
{
	return (0x00000000 | ((m) & 0xFFFFFFFF));
}
/*
int		ft_get_r(int trgb)
{
	return ((trgb & (0xFF << 16)) / 255 / 255);
}

int		ft_get_g(int trgb)
{
	return ((trgb & (0xFF << 8)) / 255);
}

int		ft_get_b(int trgb)
{
	return (trgb & 0xFF);
}
*/
static void put_color(int fd, int color)
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    b = (unsigned char)(ft_get_b(color));
    g = (unsigned char)(ft_get_g(color));
    r = (unsigned char)(ft_get_r(color));
    write(fd, &b, sizeof(b));
    write(fd, &g, sizeof(g));
    write(fd, &r, sizeof(r));
}

void    save_image(t_data *mlx_s)
{
 /*   unsigned int m;
    unsigned char i;

    m = 0x00F000FF;
    printf("%i\n", (i = 0x00000000 | ((m >> 16) & 0xFFFFFFFF)));
*/
    int fd;
    int i;
    int j;
    //int mod;
    int color;
   // unsigned char z = 0;
    
    i = mlx_s->height + 1;
    //if (mlx_s->width % 4)
      //  mod = mlx_s->width + (4 - mlx_s->width % 4);
    //else
     //   mod = mlx_s->width;
    if ((fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, 77777)) == -1)
        no_file();
    init_header(fd, (mlx_s->width * 3 * mlx_s->height));
    init_infoheader(fd, mlx_s->height, mlx_s->width);
    while(--i >= 0)
    {
        j = 0;
        while(++j <= mlx_s->width)
        {
           /* if (j > mlx_s->width)
                write(fd, &z, 1);
            else
            {*/
                mlx_pixel_get_2(mlx_s, j, i, &color);
                put_color(fd, color);
            //}
        }
        printf("\n%i\n", i);
    }
    printf("\n%i\n", fd);
    if(close(fd) < 0)
        printf("Close fail\n");
    exit(EXIT_SUCCESS);

}