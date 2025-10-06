NAME	=	cub3D

CC		=	cc

CFLAGS	= -Wall -Wextra -Werror

MLX_PATH = minilibx-linux/

MLX_LIB = $(MLX_PATH)libmlx.a

MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz


SRCS	=	./main.c\
			./src/map/check_map.c\
			./src/map/background.c\
			./src/parser/parser.c\
			./src/parser/parser2.c\
			./src/parser/parser3.c\
			./src/parser/parser4.c\
			./src/free/free.c\
			./src/init/init_b.c\
			./src/init/init.c\
			./src/init/init_player.c\
			./src/init/init_t_game.c\
			./src/free/cleanup.c\
			./src/exec/hooks.c\
			./src/exec/player.c\
			./src/utils/utils_b.c\
			./src/utils/utils_b_2.c\
			./src/utils/utils_b_3.c\
			./src/2d/2d_map.c\
			./src/raycaster/raycaster.c

OBJS	=	${SRCS:.c=.o}

LIBPATH = libft/

LIBFT = $(LIBPATH)libft.a


all: compile ${NAME}

compile:
		@make -C ${MLX_PATH} all
		@make -C ${LIBPATH}

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

clean:
		make -C $(MLX_PATH) clean
		make -C ${LIBPATH} clean
		rm -f $(OBJS)

fclean: clean
			make fclean -C ${LIBPATH}
			rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re compile

