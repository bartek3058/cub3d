NAME	=	cub3D

CC		=	cc

CFLAGS	= -Wall -Wextra -Werror

MLX_PATH = minilibx-linux/

MLX_LIB = $(MLX_PATH)libmlx.a

MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm


SRCS	=	./main.c\
					
				
OBJS	=	${SRCS:.c=.o}


all: compile ${NAME}

compile:
		@make -C ${MLX_PATH} all

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
		make -C $(MLX_PATH) clean
		rm -f $(OBJS)

fclean: clean
			rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re compile

