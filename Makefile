NAME	= so_long
CFLAGS	= -Wextra -Wall -Werror
LIBMLX	= ./lib/MLX42
LIBFT	= ./lib/libft
MAND	= ./src/mandatory

HEADERS	= -I $(LIBMLX)/include -I $(LIBFT)
LIBS	= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -pthread -lm -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

SRCS	= $(MAND)/main.c $(MAND)/draw_images.c $(MAND)/draw_map.c $(MAND)/draw_sprites.c $(MAND)/draw_tiles.c \
		  $(MAND)/error_handling.c $(MAND)/parse_map.c $(MAND)/utils.c $(MAND)/validate_map.c $(MAND)/flood_fill.c \
		  $(MAND)/get_distance.c $(MAND)/text_hook.c $(MAND)/text_hook_2.c $(MAND)/game_keyhook.c $(MAND)/game_keyhook_utils.c
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