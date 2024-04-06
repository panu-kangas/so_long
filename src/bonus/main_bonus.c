#include "so_long_bonus.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	set_window_size_and_enemies(t_game *game)
{
	game->window_width = game->map_width * 70;
	game->window_height = game->map_height * 70;
	if (game->window_width > 1050)
	{
		game->window_width = 1050;
		game->map_is_big = 1;
	}
	if (game->window_height > 700)
	{
		game->window_height = 700;
		game->map_is_big = 1;
	}
	set_enemies(game);
}

void	check_args(t_game *game, int argc, char **argv)
{
	char	*temp;

	if (argc != 2)
		error_exit(game, NULL, \
		"Invalid number of arguments! Insert one map-file.");
	temp = ft_strrchr(argv[1], '.');
	if (temp == NULL)
		error_exit(game, NULL, \
		"Invalid file type! Only files with '.ber' extension are accepted");
	if (ft_strncmp(temp, ".ber", 5) != 0)
		error_exit(game, NULL, \
		"Invalid file type! Only files with '.ber' extension are accepted");
	game->map_file_fd = open(argv[1], O_RDONLY);
	if (game->map_file_fd < 0)
		sys_error_exit(game, NULL, "Open failed");
}

void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->map = NULL;
	game->map_file_str = NULL;
	game->left_right = 'R';
	game->map_file_fd = -2;
	game->map_is_big = 0;
	game->map_height = 0;
	game->map_width = 0;
	game->window_height = 0;
	game->window_width = 0;
	game->collectible_count = 0;
	game->f_count = 0;
	game->draw_coord[0] = 0;
	game->draw_coord[1] = 0;
	game->collectible_img_i = 0;
	game->attack = 0;
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	game = malloc(1 * sizeof(t_game));
	if (game == NULL)
		sys_error_exit(game, NULL, "Malloc failed");
	init_game_struct(game);
	check_args(game, argc, argv);
	parse_map(game);
	set_window_size_and_enemies(game);
	game->mlx = mlx_init(game->window_width, game->window_height + 40, \
	"so_long", false);
	if (!game->mlx)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	draw_map(game, 0);
	mlx_loop_hook(game->mlx, &enemy_hook, game);
	mlx_loop_hook(game->mlx, &text_hook, game);
	mlx_loop_hook(game->mlx, &animation_hook, game);
	mlx_key_hook(game->mlx, &game_keyhook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	if (game->map_file_fd >= 0)
		close(game->map_file_fd);
	ft_free_game_struct(game);
	end_message();
	return (0);
}
