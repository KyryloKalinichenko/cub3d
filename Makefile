# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 15:41:54 by kkalinic          #+#    #+#              #
#    Updated: 2021/05/19 11:23:15 by kkalinic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	cub3d.c \
					get_next_line/get_next_line_bonus.c \
					get_next_line/get_next_line_utils_bonus.c \
					other_functions/init.c \
					old_lib/ft_atoi.c \
					old_lib/ft_split.c \
					old_lib/ft_isdigit.c \
					old_lib/ft_strlcpy.c \
					texturation/draw.c \
					raycasting/ray_fun.c \
					other_functions/errors_f.c \
					parsing/map_check.c \
					texturation/init_text.c \
					other_functions/save_image.c \
					parsing/height_count.c \
					texturation/pixel_move.c \
					other_functions/sort.c \
					parsing/parsing.c \
					other_functions/tools.c \
					parsing/extra_cheking.c \
					texturation/sprites.c \
					other_functions/turns_moves.c	\
					parsing/start_pos.c \

SRCS_B			=	cub3d.c \
					get_next_line/get_next_line_bonus.c \
					get_next_line/get_next_line_utils_bonus.c \
					bonus_f/init.c \
					old_lib/ft_atoi.c \
					old_lib/ft_split.c \
					old_lib/ft_isdigit.c \
					old_lib/ft_strlcpy.c \
					texturation/draw.c \
					bonus_f/ray_fun_bonus.c \
					other_functions/errors_f.c \
					parsing/map_check.c \
					texturation/init_text.c \
					other_functions/save_image.c \
					parsing/height_count.c \
					texturation/pixel_move.c \
					other_functions/sort.c \
					parsing/parsing.c \
					other_functions/tools.c \
					parsing/extra_cheking.c \
					texturation/sprites.c \
					other_functions/turns_moves.c	\
					parsing/start_pos.c \
					bonus_f/print_hud/print_minimap_bonus.c \
					bonus_f/floor_tex/floor_bonus.c
					

OBJS			= $(SRCS:.c=.o)
OBJS_B			= $(SRCS_B:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX				=  libmlx.a

NAME			= cub3D
BONUS			= bonus

MAP	=	maps/map.cub

all:			$(NAME) $(BONUS)

run:
				./${NAME} $(MAP)

$(NAME):		$(OBJS) $(MLX)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} $(MLX) ${LIBS}

$(BONUS):	$(OBJS_B) $(MLX)
			gcc ${CFLAGS_B} -o ${BONUS} ${OBJS_B} $(MLX) ${LIBS}

$(MLX):
			cd mlx/ && $(MAKE) && mv $(MLX) ../

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(OBJS_B)

fclean:			clean
				$(RM) $(NAME) $(BONUS) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
