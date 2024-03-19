#include "so_long.h"

/* void 	close_hook(void *param) // IS THIS NEEDED ?!
{
	t_game		*game;

	game = param;

	mlx_terminate(game->mlx);

	if (game->map_file_fd >= 0)
		close(game->map_file_fd);
	ft_free_game_struct(game);
	exit(0);
} */

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
		game->window_width = 1050; // Check the max value !
		game->map_is_big = 1;
	}
	if (game->window_height > 700)
	{
		game->window_height = 700; // Check the max value !
		game->map_is_big = 1;
	}
}

void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->player_img = NULL;
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
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	int		window_width;
	int		window_height;

	game = malloc(1 * sizeof(t_game));
	if (game == NULL)
		sys_error_exit(game, NULL, "Malloc failed");
	init_game_struct(game);
	check_args(game, argc, argv);
	parse_map(game);
	set_window_size(game);
	window_width = game->window_width;
	window_height = game->window_height;
	game->mlx = mlx_init(window_width, window_height + 50, "so_long", false);
	if (!game->mlx)
		return (1); // error_exit, should this be like a separate MLX-error -function...?
	get_c_count(game);
	draw_map(game);


	mlx_loop_hook(game->mlx, &text_hook, game);
	mlx_key_hook(game->mlx, &game_keyhook, game);
//	mlx_close_hook(game->mlx, &close_hook, game); // IS THIS NEEDED ?!


	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);

	if (game->map_file_fd >= 0)
		close(game->map_file_fd);
	ft_free_game_struct(game);
	
	return (0);
}