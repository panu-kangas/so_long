/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_checks_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:33:52 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:33:54 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_hammer_hit(t_game *game)
{
	int	i;
	int	dir_effect;
	int	instance;

	game->attack = 1;
	if (game->left_right == 'R')
		dir_effect = 1;
	else
		dir_effect = -1;
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].is_dying == 0 && \
		game->enemies[i].x == game->player_coord[0] + dir_effect \
		&& game->enemies[i].y == game->player_coord[1])
		{
			instance = game->enemies[i].instance;
			game->enemy_img[game->enemy_img_i]->instances[instance].enabled = 0;
			game->enemies[i].is_dying = 1;
		}
		i++;
	}
}

void	check_for_esc(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		if (game->map_file_fd >= 0)
			close(game->map_file_fd);
		mlx_terminate(game->mlx);
		ft_free_game_struct(game);
		end_message();
		exit(0);
	}
}

void	check_for_wasdh(t_game *game, int prev_hammer)
{
	int	time;

	time = mlx_get_time();
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) \
	&& check_wall(game, 1) == 0 && game->attack == 0)
		move_player(game, 'W');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) \
	&& check_wall(game, 2) == 0 && game->attack == 0)
		move_player(game, 'S');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) \
	&& check_wall(game, 3) == 0 && game->attack == 0)
		move_player(game, 'A');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D) \
	&& check_wall(game, 4) == 0 && game->attack == 0)
		move_player(game, 'D');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_H) \
	&& time > prev_hammer + 0.2 && game->attack == 0)
	{
		check_hammer_hit(game);
		prev_hammer = time;
	}
}

void	check_for_collectible(t_game *game)
{
	int			player_x;
	int			player_y;
	int			i;
	int			instance;

	player_x = game->player_coord[0];
	player_y = game->player_coord[1];
	i = game->collectible_img_i;
	if (game->map[player_y][player_x].type == 'C')
	{
		game->collectible_count--;
		instance = game->map[player_y][player_x].c_instance;
		game->collectible_img[i]->instances[instance].enabled = 0;
		game->map[player_y][player_x].type = '0';
	}
	if (game->collectible_count == -2)
		game->map[game->exit_co[1]][game->exit_co[0]].dist_to_player--;
}
