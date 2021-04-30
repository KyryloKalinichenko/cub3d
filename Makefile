
SRCS			=	cub3d.c \
					get_next_line/get_next_line_bonus.c \
					get_next_line/get_next_line_utils_bonus.c \
					init.c \
					ft_atoi.c \
					ft_split.c \
					ft_isdigit.c \
					ft_strlcpy.c \
					draw.c \
					print_player.c \
					ray_fun.c \
					errors_f.c \
					map_check.c \
					init_text.c \
					save_image.c \
					

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX				=  libmlx.dylib

NAME			= cub3D

MAP	=	map.cub

all:			$(NAME)

run:
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS} && ./${NAME} $(MAP)

$(NAME):		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS} 

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re