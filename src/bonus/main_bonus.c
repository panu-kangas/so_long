#include "so_long_bonus.h"

void	get_c_count(t_game *game)
{
	int	i;

	i = 0;
	while (game->map_file_str[i] != '\0')
	{
		if (game->map_file_str[i] == 'C')
			game->collectible_count++;
		i++;
	}
}

void	set_window_size(t_game *game)
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
	int	i;

	game->mlx = NULL;
	i = -1;
	while (++i < 7)
		game->player_img[i] = NULL;
	game->collectible_img = NULL;
	game->exit_img[0] = NULL;
	game->exit_img[1] = NULL;
	game->c_text = NULL;
	game->c_text2 = NULL;
	game->c_num = NULL;
	game->map = NULL;
	game->map_file_str = NULL;
	game->map_file_fd = -2;
	game->map_is_big = 0;
	game->map_height = 0;
	game->map_width = 0;
	game->window_height = 0;
	game->window_width = 0;
	game->collectible_count = 0;
	game->draw_coord[0] = 0;
	game->draw_coord[1] = 0;
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
	set_window_size(game);
	game->mlx = mlx_init(game->window_width, game->window_height + 60, \
	"so_long", false);
	if (!game->mlx)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	get_c_count(game);
	draw_map(game, 0);

	mlx_loop_hook(game->mlx, &text_hook, game);
	mlx_key_hook(game->mlx, &game_keyhook, game);
	mlx_loop_hook(game->mlx, &animation_hook, game);


	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	if (game->map_file_fd >= 0)
		close(game->map_file_fd);
	ft_free_game_struct(game);
	return (0);
}
