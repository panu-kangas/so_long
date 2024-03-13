#include "so_long.h"

void	write_ending(t_game *game, char *str)
{
	mlx_image_t *end_txt;
	mlx_image_t *end_txt2;

	mlx_delete_image(game->mlx, game->c_text);
	mlx_delete_image(game->mlx, game->c_text2);
	mlx_delete_image(game->mlx, game->c_num);
	end_txt = mlx_put_string(game->mlx, str, 0, game->mlx->height - 50);
	if (end_txt == NULL)
		return ; // MLX_error_exit
	end_txt2 = mlx_put_string(game->mlx, "Press ESC to exit game", \
	0, game->mlx->height - 30);
	if (end_txt2 == NULL)
		return ; // MLX_error_exit
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

	find_char_in_map(game, 'E', coord); // I should fix this probably, so that I use the struct info
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
		game->c_num = mlx_put_string(game->mlx, ft_itoa(move_count), \
		460, game->mlx->height - 30);
		if (game->c_num == NULL)
			return ; // MLX_error_exit
		move_count_prev = move_count;
	}
}

void	change_c_count_text(t_game *game, int c_count_prev, int c_count)
{
	if (c_count_prev > c_count && c_count > 0)
	{
		mlx_delete_image(game->mlx, game->c_num);
		game->c_num = NULL;
		game->c_num = mlx_put_string(game->mlx, ft_itoa(c_count), \
		150, game->mlx->height - 30);
		if (game->c_num == NULL)
			return ; // MLX_error_exit
		c_count_prev = c_count;
	}
}

void	is_all_collected(t_game *game, int c_count)
{
	int	move_count;
	int	exit_x;
	int	exit_y;

	if (c_count == 0)
	{
		mlx_delete_image(game->mlx, game->c_text);
		game->c_text = NULL;
		mlx_delete_image(game->mlx, game->c_text2);
		game->c_text2 = NULL;
		mlx_delete_image(game->mlx, game->c_num);
		game->c_num = NULL;
		get_dist_to_player(game);
		exit_x = game->exit_coord[0];
		exit_y = game->exit_coord[1];
		move_count = game->map[exit_y][exit_x].dist_to_player;
		game->c_text = mlx_put_string(game->mlx, "Yay, you got them! =)", \
		0, game->mlx->height - 50);
		if (game->c_text == NULL)
			return ; // MLX_error_exit
		game->c_text2 = mlx_put_string(game->mlx, \
		"Move to exit as fast as you can.  Moves left: ", 0, game->mlx->height - 30);
		if (game->c_text2 == NULL)
			return ; // MLX_error_exit
		game->c_num = mlx_put_string(game->mlx, ft_itoa(move_count), \
		460, game->mlx->height - 30);
		if (game->c_num == NULL)
			return ; // MLX_error_exit
		// CHANGE EXIT IMAGE !
		game->collectible_count = -1;
	}
}

void	text_hook(void *param)
{
	t_game 		*game;
	static int	c_count_prev;
	static int	text_flag;
	int			c_count;

	game = param;
	c_count = game->collectible_count;
	if (text_flag == 0)
	{
		c_count_prev = c_count;
		game->c_text = mlx_put_string(game->mlx, \
		"Wow, nice, diamonds! Go catch them all!", 0, game->mlx->height - 50);
		game->c_text2 = mlx_put_string(game->mlx, "Diamond count: ", \
		0, game->mlx->height - 30);
		if (game->c_text2 == NULL)
			return ; // MLX_error_exit
		game->c_num = mlx_put_string(game->mlx, ft_itoa(c_count), \
		150, game->mlx->height - 30);
		if (game->c_num == NULL)
			return ; // MLX_error_exit
		text_flag = 1;
	}
	is_all_collected(game, c_count);
	change_c_count_text(game, c_count_prev, game->collectible_count);
	change_move_count_text(game, game->collectible_count);
	is_game_over(game);
}