/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_hook_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:35:02 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:35:03 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	move_count_to_window(t_game *game, int move_count)
{
	char	*num;

	mlx_delete_image(game->mlx, game->c_num);
	game->c_num = NULL;
	num = ft_itoa(move_count);
	if (num == NULL)
		sys_error_exit(game, game->mlx, "Malloc failed");
	game->c_num = mlx_put_string(game->mlx, num, \
	120, game->mlx->height - 20);
	free(num);
	num = NULL;
	if (game->c_num == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	return (move_count);
}

void	write_ending(t_game *game, char *str)
{
	mlx_image_t	*end_txt;
	mlx_image_t	*end_txt2;

	mlx_delete_image(game->mlx, game->c_text);
	mlx_delete_image(game->mlx, game->c_text2);
	mlx_delete_image(game->mlx, game->c_num);
	end_txt = mlx_put_string(game->mlx, str, 0, game->mlx->height - 40);
	if (end_txt == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	end_txt2 = mlx_put_string(game->mlx, "Press ESC to exit", \
	0, game->mlx->height - 20);
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
	exit_x = game->exit_co[0];
	exit_y = game->exit_co[1];
	c_count = game->collectible_count;
	if (game->map[exit_y][exit_x].dist_to_player == 0 && c_count == -2)
	{
		if (player_x == exit_x && player_y == exit_y)
			write_ending(game, "YOU WIN!!! =)");
		else
			write_ending(game, "You lose =(");
		game->collectible_count = -3;
	}
}

void	find_exit_in_window(t_game *game)
{
	int	x;
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
				if (mlx_image_to_window(game->mlx, game->exit_img[1], \
				j * 70, i * 70) < 0)
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
	if (game->map_x_is_big == 0 && game->map_y_is_big == 0)
		mlx_set_instance_depth(&game->exit_img[1]->instances[0], 2);
	else
		find_exit_in_window(game);
}
