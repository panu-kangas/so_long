#include "so_long.h"

void	check_for_collectible(t_game *game)
{
	int			player_x;
	int			player_y;
	int			exit_x;
	int			exit_y;

	player_x = game->player_coord[0];
	player_y = game->player_coord[1];
	if (game->map[player_y][player_x].type == 'C')
	{
		game->collectible_count--;
		game->map[player_y][player_x].instance->enabled = 0;
		game->map[player_y][player_x].type = '0';
	}
	exit_x = game->exit_coord[0];
	exit_y = game->exit_coord[1];
	if (game->collectible_count == -2)
		game->map[exit_y][exit_x].dist_to_player--;
}

void	move_player(t_game *game, char c)
{
	static int	counter;

	if (c == 'W')
	{
		game->player_img->instances[0].y -= 70;
		game->player_coord[1] -= 1;
	}
	else if (c == 'S')
	{
		game->player_img->instances[0].y += 70;
		game->player_coord[1] += 1;
	}
	else if (c == 'A')
	{
		game->player_img->instances[0].x -= 70;
		game->player_coord[0] -= 1;
	}
	else if (c == 'D')
	{
		game->player_img->instances[0].x += 70;
		game->player_coord[0] += 1;
	}
	check_for_collectible(game);
	ft_printf("Number of movements: %d\n", ++counter);
}

int	check_for_wall(t_game *game, int num)
{
	int	x;
	int	y;

	x = game->player_img->instances[0].x / 70;
	y = game->player_img->instances[0].y / 70;
	
	if (num == 1 && game->map[y - 1][x].type == '1')
		return (1);
	else if (num == 2 && game->map[y + 1][x].type == '1')
		return (1);
	else if (num == 3 && game->map[y][x - 1].type == '1')
		return (1);
	else if (num == 4 && game->map[y][x + 1].type == '1')
		return (1);
	return (0);
}

void	game_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game		*game;

	game = param;

	if (game->collectible_count != -3)
	{
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && check_for_wall(game, 1) == 0)
			move_player(game, 'W');
		if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && check_for_wall(game, 2) == 0)
			move_player(game, 'S');
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && check_for_wall(game, 3) == 0)
			move_player(game, 'A');
		if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && check_for_wall(game, 4) == 0)
			move_player(game, 'D');
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		write_error(game, game->mlx, NULL);
}


int	main(int argc, char *argv[])
{
	t_game	*game;
	int		window_width;
	int		window_height;

	game = malloc(1 * sizeof(t_game));
	if (game == NULL)
		write_sys_error(game, NULL, "Malloc failed");

	game->mlx = NULL;
	game->player_img = NULL;
	game->collectible_img = NULL;
	game->exit_img = NULL;
	game->c_text = NULL;
	game->c_num = NULL;
	game->map = NULL;
	game->map_file_str = NULL;
	game->map_file_fd = -2;
	game->collectible_count = 0;

	check_args(game, argc, argv);

	parse_map(game);


	window_width = game->map_line_len * 70;
	window_height = game->map_line_count * 70;
	if (window_width > 1000)
		window_width = 1000; // Check the max value !
	if (window_height > 700)
		window_height = 700; // Check the max value !
	game->mlx = mlx_init(window_width, window_height + 50, "so_long", false);
	if (!game->mlx)
		return (1); // error_exit, should this be like a separate MLX-error -function...?


	draw_all(game);



	// hook also needs to check that if map > screen size, the map needs to move when player moves
	mlx_key_hook(game->mlx, &game_keyhook, game);
	mlx_loop_hook(game->mlx, &text_hook, game);


	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);

	// free everything you allocated: game-struct etc
	// I might need to free textures separately
	// close that one fd!!

	return (0);

}