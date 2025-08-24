NAME	=	cub3D

CC		=	cc

CFLAGS	= -Wall -Wextra -Werror

MLX_PATH = minilibx-linux/

MLX_LIB = $(MLX_PATH)libmlx.a

MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz


SRCS	=	./main.c\
			./src/map/check_map.c\
			./src/parser/parser.c\
			./src/parser/parser2.c\
			./src/free/free.c\
			./src/init/init_b.c\
					
				
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

