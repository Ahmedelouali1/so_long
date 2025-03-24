NAME = so_long
CC = gcc
CFLAGC = -Wall - Wextra -Werror
MLX = 

SRCS = check_maps.c check_valid_path.c read_map.c
OBJS = $(SRCS: .c = .o)

all : $(NAME)

$(NAME) : $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) $(MLX) -o (NAME)

clean :
    rm -f $(OBJS)

fclean : clean
    rm -f $(NAME)

re : fclean all