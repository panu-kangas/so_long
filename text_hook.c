#include "so_long.h"

void	write_ending(t_game *game, char *str)
{
	mlx_image_t *end_txt;
	mlx_image_t *end_txt2;

	mlx_delete_image(game->mlx, game->c_text);
	mlx_delete_image(game->mlx, game->c_text2);
	mlx_delete_image(game->mlx, game->c_num);
	end_txt = mlx_put_string(game->mlx, str, 10, game->mlx->height - 50);
	if (end_txt == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	end_txt2 = mlx_put_string(game->mlx, "Press ESC to exit game", \
	10, game->mlx->height - 30);
	if (end_txt2 == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
}

void	is_game_over(t_game *game)
{
	int	player_x;
	int	player_y;
	int	exit_x;
	int	exit_y;
	int	c_count;

	player_x = game->player_coord[0];
	player_y = game->player_coord[1];
	exit_x = game->exit_coord[0];
	exit_y = game->exit_coord[1];
	c_count = game->collectible_count;
	if (game->map[exit_y][exit_x].dist_to_player == 0 && c_count == -2)
	{
		if (player_x == exit_x && player_y == exit_y)
			write_ending(game, "YOU WIN!!! Great job =)");
		else
			write_ending(game, "You lose, sorry =(");
		game->collectible_count = -3;
	}
}

void	change_move_count_text(t_game *game, int c_count)
{
	int 		coord[2];
	int			move_count;
	static int	move_count_prev;
	char		*num;

	coord[0] = game->exit_coord[0];
	coord[1] = game->exit_coord[1];
	move_count = game->map[coord[1]][coord[0]].dist_to_player;
	if (c_count == -1)
	{
		move_count_prev = move_count;
		game->collectible_count = -2;
	}
	if (c_count == -2 && move_count_prev > move_count)
	{
		mlx_delete_image(game->mlx, game->c_num);
		game->c_num = NULL;
		num = ft_itoa(move_count);
		if (num == NULL)
			sys_error_exit(game, game->mlx, "Malloc failed");
		game->c_num = mlx_put_string(game->mlx, num, \
		520, game->mlx->height - 30);
		free(num);
		if (game->c_num == NULL)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		move_count_prev = move_count;
	}
}

void	change_c_count_text(t_game *game, int c_count_prev, int c_count)
{
	char	*num;

	if (c_count_prev > c_count && c_count > 0)
	{
		mlx_delete_image(game->mlx, game->c_num);
		game->c_num = NULL;
		num = ft_itoa(c_count);
		if (num == NULL)
			sys_error_exit(game, game->mlx, "Malloc failed");
		game->c_num = mlx_put_string(game->mlx, num, \
		160, game->mlx->height - 30);
		free(num);
		if (game->c_num == NULL)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		c_count_prev = c_count;
	}
}

void	find_exit_in_window(t_game *game)
{
	int x;
	int	y;
	int	i;
	int	j;

	y = get_y_start(game);
	i = -1;
	while (++i < (game->window_height / 70))
	{
		x = get_x_start(game);
		j = -1;
		while (++j < (game->window_width / 70))
		{
			if (game->map[y][x].type == 'E')
			{
				mlx_delete_image(game->mlx, game->exit_img[0]);
				if (mlx_image_to_window(game->mlx, game->exit_img[1], j * 70, i * 70) < 0)
					error_exit(game, game->mlx, mlx_strerror(mlx_errno));
				mlx_set_instance_depth(&game->exit_img[1]->instances[0], 2);
			}
			x++;
		}
		y++;
	}
}

void	delete_text_images(t_game *game)
{
	mlx_delete_image(game->mlx, game->c_text);
	game->c_text = NULL;
	mlx_delete_image(game->mlx, game->c_text2);
	game->c_text2 = NULL;
	mlx_delete_image(game->mlx, game->c_num);
	game->c_num = NULL;
	if (game->map_is_big == 0)
		mlx_set_instance_depth(&game->exit_img[1]->instances[0], 2);
	else 
		find_exit_in_window(game);
}

void	is_all_collected(t_game *game, int c_count)
{
	int		move_count;
	int		exit_x;
	int		exit_y;
	char	*num;

	if (c_count == 0)
	{
		delete_text_images(game);
		get_dist_to_player(game);
		exit_x = game->exit_coord[0];
		exit_y = game->exit_coord[1];
		move_count = game->map[exit_y][exit_x].dist_to_player;
		game->c_text = mlx_put_string(game->mlx, "Yay, you got them! =)", \
		10, game->mlx->height - 50);
		if (game->c_text == NULL)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		game->c_text2 = mlx_put_string(game->mlx, \
		"Now, move to exit as fast as you can.  Moves left: ", 10, game->mlx->height - 30);
		if (game->c_text2 == NULL)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		num = ft_itoa(move_count);
		if (num == NULL)
			sys_error_exit(game, game->mlx, "Malloc failed");
		game->c_num = mlx_put_string(game->mlx, num, \
		520, game->mlx->height - 30);
		free(num);
		if (game->c_num == NULL)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		game->collectible_count = -1;
	}
}

void	text_hook(void *param)
{
	t_game 		*game;
	static int	c_count_prev;
	static int	text_flag;
	int			c_count;
	char		*num;

	game = param;
	c_count = game->collectible_count;
	if (text_flag == 0)
	{
		c_count_prev = c_count;
		game->c_text = mlx_put_string(game->mlx, \
		"Wow, diamonds! Go catch them all!", 10, game->mlx->height - 50);
		game->c_text2 = mlx_put_string(game->mlx, "Diamond count: ", \
		10, game->mlx->height - 30);
		if (game->c_text2 == NULL)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		num = ft_itoa(c_count);
		if (num == NULL)
			sys_error_exit(game, game->mlx, "Malloc failed");
		game->c_num = mlx_put_string(game->mlx, num, \
		160, game->mlx->height - 30);
		free(num);
		if (game->c_num == NULL)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		text_flag = 1;
	}
	is_all_collected(game, c_count);
	change_c_count_text(game, c_count_prev, game->collectible_count);
	change_move_count_text(game, game->collectible_count);
	is_game_over(game);
}