/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:29:05 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:29:07 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	change_move_count_text(t_game *game, int c_count)
{
	int			coord[2];
	int			move_count;
	static int	move_count_prev;

	coord[0] = game->exit_co[0];
	coord[1] = game->exit_co[1];
	move_count = game->map[coord[1]][coord[0]].dist_to_player;
	if (c_count == -1)
	{
		move_count_prev = move_count;
		game->collectible_count = -2;
	}
	if (c_count == -2 && move_count_prev > move_count)
		move_count_prev = move_count_to_window(game, move_count);
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

void	all_collected(t_game *game)
{
	int		move_count;
	char	*num;

	delete_text_images(game);
	get_dist_to_player(game);
	move_count = game->map[game->exit_co[1]][game->exit_co[0]].dist_to_player;
	game->c_text = mlx_put_string(game->mlx, "Now, move to exit!", \
	10, game->mlx->height - 50);
	if (game->c_text == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->c_text2 = mlx_put_string(game->mlx, \
	"Moves left: ", 10, game->mlx->height - 30);
	if (game->c_text2 == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	num = ft_itoa(move_count);
	if (num == NULL)
		sys_error_exit(game, game->mlx, "Malloc failed");
	game->c_num = mlx_put_string(game->mlx, num, \
	130, game->mlx->height - 30);
	free(num);
	num = NULL;
	if (game->c_num == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->collectible_count = -1;
}

int	start_text_to_window(t_game *game, int c_count)
{
	char	*num;

	game->c_text = mlx_put_string(game->mlx, "Get the diamonds!", \
	10, game->mlx->height - 50);
	if (game->c_text == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
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
	num = NULL;
	if (game->c_num == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	return (1);
}

void	text_hook(void *param)
{
	t_game		*game;
	static int	c_count_prev;
	static int	text_flag;
	int			c_count;

	game = param;
	c_count = game->collectible_count;
	if (text_flag == 0)
	{
		c_count_prev = c_count;
		text_flag = start_text_to_window(game, c_count);
	}
	if (game->collectible_count == 0)
		all_collected(game);
	change_c_count_text(game, c_count_prev, game->collectible_count);
	change_move_count_text(game, game->collectible_count);
	is_game_over(game);
}
