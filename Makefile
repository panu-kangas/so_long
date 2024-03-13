NAME	= so_long
CFLAGS	= -Wextra -Wall -Werror
LIBMLX	= ./lib/MLX42
LIBFT	= ./lib/libft

HEADERS	= -I $(LIBMLX)/include -I $(LIBFT)
LIBS	= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm

SRCS	= main.c draw_images.c error_handling.c parse_map.c utils.c validate_map.c flood_fill.c \
			get_distance.c text_hook.c
OBJS	= ${SRCS:.c=.o}

all: libmlx libft $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	make -C $(LIBFT)

# is this ok ?? It is needed so that .c files can find headers
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -f $(OBJS)
	make fclean -C $(LIBFT)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft