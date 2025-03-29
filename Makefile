NAME = so_long
CC = gcc
MLX = -I minilibx-linux -L minilibx-linux -lmlx_Linux -lXext -lX11 -lXext -lX11 -lm -lz
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
INCLUDE = so_long.h Makefile
SRCS = check_map.c check_valid_path.c so_long.c ft_split.c get_next_line.c \
	get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

%.o : %.c ${INCLUDE}
	${CC} ${CFLAGS} -o $@ -c $<

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all