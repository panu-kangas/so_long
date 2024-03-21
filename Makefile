NAME	= so_long
CFLAGS	= -Wextra -Wall -Werror
LIBMLX	= ./lib/MLX42/build/libmlx42.a
LIBFT	= ./lib/libft/libft.a
MAND	= ./src/mandatory
BONUS	= ./src/bonus

HEADERS	= -I ./lib/MLX42/include -I ./lib/libft
LIBS	= $(LIBMLX) $(LIBFT) -ldl -pthread -lm -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

SRCS	= $(MAND)/main.c $(MAND)/draw_images.c $(MAND)/draw_map.c $(MAND)/draw_sprites.c $(MAND)/draw_tiles.c \
		  $(MAND)/error_handling.c $(MAND)/parse_map.c $(MAND)/utils.c $(MAND)/validate_map.c $(MAND)/flood_fill.c \
		  $(MAND)/get_distance.c $(MAND)/text_hook.c $(MAND)/text_hook_2.c $(MAND)/game_keyhook.c $(MAND)/game_keyhook_utils.c
OBJS	= ${SRCS:.c=.o}

BONSRCS	= $(BONUS)/main_bonus.c $(BONUS)/draw_images_bonus.c $(BONUS)/draw_map_bonus.c $(BONUS)/draw_sprites_bonus.c \
		  $(BONUS)/draw_tiles_bonus.c $(BONUS)/error_handling_bonus.c $(BONUS)/parse_map_bonus.c \
		  $(BONUS)/utils_bonus.c $(BONUS)/validate_map_bonus.c $(BONUS)/flood_fill_bonus.c \
		  $(BONUS)/get_distance_bonus.c $(BONUS)/text_hook_bonus.c $(BONUS)/text_hook_2_bonus.c \
		  $(BONUS)/game_keyhook_bonus.c $(BONUS)/game_keyhook_utils_bonus.c $(BONUS)/animations_bonus.c
BONOBJS	= ${BONSRCS:.c=.o}

all: $(LIBMLX) $(LIBFT) $(NAME)

$(LIBMLX):
	cmake ./lib/MLX42 -B ./lib/MLX42/build && make -C ./lib/MLX42/build -j4

$(LIBFT):
	make -C ./lib/libft/.

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

bonus: .bonus

.bonus: $(LIBMLX) $(LIBFT) $(BONOBJS)
	$(CC) $(BONOBJS) $(LIBS) $(HEADERS) -o $(NAME)
	touch .bonus

# is this ok ?? It is needed so that .c files can find headers
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	rm -f $(OBJS)
	rm -f $(BONOBJS)
	make fclean -C ./lib/libft/.
	rm -rf ./lib/MLX42/build
	rm -f .bonus

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, bonus