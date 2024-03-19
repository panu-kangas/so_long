#include "so_long.h"

void	check_for_collectible(t_game *game)
{
	int			player_x;
	int			player_y;
	int			exit_x;
	int			exit_y;
	int			instance;

	player_x = game->player_coord[0];
	player_y = game->player_coord[1];
	if (game->map[player_y][player_x].type == 'C')
	{
		game->collectible_count--;
		instance = game->map[player_y][player_x].c_instance;
		game->collectible_img->instances[instance].enabled = 0;
		game->map[player_y][player_x].type = '0';
	}
	exit_x = game->exit_coord[0];
	exit_y = game->exit_coord[1];
	if (game->collectible_count == -2)
		game->map[exit_y][exit_x].dist_to_player--;
}


void	redraw_map(t_game *game, char c)
{
	if (c == 'W')
		game->player_coord[1] -= 1;
	else if (c == 'S')
		game->player_coord[1] += 1;
	else if (c == 'A')
		game->player_coord[0] -= 1;
	else if (c == 'D')
		game->player_coord[0] += 1;
	check_for_collectible(game);
	mlx_delete_image(game->mlx, game->floor_img);
	game->floor_img = NULL;
	mlx_delete_image(game->mlx, game->wall_img);
	game->wall_img = NULL;
	mlx_delete_image(game->mlx, game->player_img);
	game->player_img = NULL; 
	mlx_delete_image(game->mlx, game->collectible_img);
	game->collectible_img = NULL;
	mlx_delete_image(game->mlx, game->exit_img[0]);
	game->exit_img[0] = NULL;
	mlx_delete_image(game->mlx, game->exit_img[1]);
	game->exit_img[1] = NULL;
	draw_map(game);
}

void	move_p_img(t_game *game, char c)
{
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
}

int		is_close_to_wall(t_game *game, char c)
{
	int	player_x;
	int	player_y;

	player_x = game->player_coord[0];
	player_y = game->player_coord[1];

	if ((c == 'W' || c == 'S') && (player_y <= 3 || player_y >= game->map_height - 5))
		return (0);
	if ((c == 'A' || c == 'D') && (player_x <= 6 || player_x >= game->map_width - 7))
		return (0);
	return (1);
}

void	move_player(t_game *game, char c)
{
	static int	counter;

	if (game->map_is_big == 0 || is_close_to_wall(game, c) == 0)
		move_p_img(game, c);
	else
		redraw_map(game, c);

	ft_printf("Number of movements: %d\n", ++counter);
}

int	check_for_wall(t_game *game, int num)
{
	int	x;
	int	y;

	x = game->player_coord[0];
	y = game->player_coord[1];
	
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
	{
		if (game->map_file_fd >= 0)
			close(game->map_file_fd);
		mlx_terminate(game->mlx);
		ft_free_game_struct(game);
		exit(0);
	}
}
