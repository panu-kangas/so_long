#include "so_long_bonus.h"

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
	exit_x = game->exit_co[0];
	exit_y = game->exit_co[1];
	if (game->collectible_count == -2)
		game->map[exit_y][exit_x].dist_to_player--;
}

void	redraw_map(t_game *game, char c)
{
	int	i;

	i = game->player_img_i;
	if (c == 'W')
	{
		game->player_coord[1] -= 1;
		if (game->player_coord[1] == 3)
			game->player_img[i]->instances[0].y -= 70;
	}
	else if (c == 'S')
	{
		game->player_coord[1] += 1;
		if (game->player_coord[1] == game->map_height - 5)
			game->player_img[i]->instances[0].y += 70;
	}
	else if (c == 'A')
	{
		game->player_coord[0] -= 1;
		if (game->player_coord[0] == 6)
			game->player_img[i]->instances[0].x -= 70;
	}
	else if (c == 'D')
	{
		game->player_coord[0] += 1;
		if (game->player_coord[0] == game->map_width - 7)
			game->player_img[i]->instances[0].x += 70;
	}
	check_for_collectible(game);
	mlx_delete_image(game->mlx, game->floor_img);
	game->floor_img = NULL;
	mlx_delete_image(game->mlx, game->wall_img);
	game->wall_img = NULL;
	mlx_delete_image(game->mlx, game->collectible_img);
	game->collectible_img = NULL;
	mlx_delete_image(game->mlx, game->exit_img[0]);
	game->exit_img[0] = NULL;
	mlx_delete_image(game->mlx, game->exit_img[1]);
	game->exit_img[1] = NULL;
	draw_map(game, 1);
}

void	move_p_img(t_game *game, char c)
{
	int	i;

	i = game->player_img_i;
	if (c == 'W')
	{
		game->player_img[i]->instances[0].y -= 70;
		game->player_coord[1] -= 1;
	}
	else if (c == 'S')
	{
		game->player_img[i]->instances[0].y += 70;
		game->player_coord[1] += 1;
	}
	else if (c == 'A')
	{
		game->player_img[i]->instances[0].x -= 70;
		game->player_coord[0] -= 1;
	}
	else if (c == 'D')
	{
		game->player_img[i]->instances[0].x += 70;
		game->player_coord[0] += 1;
	}
	check_for_collectible(game);
}

void	move_player(t_game *game, char c)
{
	static int	counter;
	char 		*num;

	if (game->map_is_big == 0 || is_close_to_wall(game, c) == 0)
		move_p_img(game, c);
	else
		redraw_map(game, c);
	counter++;
	mlx_delete_image(game->mlx, game->total_moves);
	game->total_moves = NULL;
	num = ft_itoa(counter);
	if (num == NULL)
		sys_error_exit(game, game->mlx, "Malloc failed");
	game->total_moves = mlx_put_string(game->mlx, num, \
	200, game->mlx->height - 20);
	free(num);
	if (game->total_moves == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));

//	ft_printf("Number of movements: %d\n", ++counter); --> IS THIS NEEDED ??
}

void	game_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game		*game;

	game = param;
	if (game->collectible_count != -3)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_W) && check_wall(game, 1) == 0)
			move_player(game, 'W');
		if (mlx_is_key_down(game->mlx, MLX_KEY_S) && check_wall(game, 2) == 0)
			move_player(game, 'S');
		if (mlx_is_key_down(game->mlx, MLX_KEY_A) && check_wall(game, 3) == 0)
			move_player(game, 'A');
		if (mlx_is_key_down(game->mlx, MLX_KEY_D) && check_wall(game, 4) == 0)
			move_player(game, 'D');
		if (mlx_is_key_down(game->mlx, MLX_KEY_R))
			game->attack = 1;
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
