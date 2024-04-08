/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keyhook_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:33:25 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:33:26 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	change_player_coord_for_redraw(t_game *game, char c, int i)
{
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
}

void	redraw_map(t_game *game, char c)
{
	int	i;

	i = game->player_img_i;
	change_player_coord_for_redraw(game, c, i);
	check_for_hit(game);
	check_for_collectible(game);
	mlx_delete_image(game->mlx, game->floor_img);
	game->floor_img = NULL;
	mlx_delete_image(game->mlx, game->wall_img);
	game->wall_img = NULL;
	mlx_delete_image(game->mlx, game->collectible_img[game->collectible_img_i]);
	game->collectible_img[game->collectible_img_i] = NULL;
	mlx_delete_image(game->mlx, game->exit_img[0]);
	game->exit_img[0] = NULL;
	mlx_delete_image(game->mlx, game->exit_img[1]);
	game->exit_img[1] = NULL;
	mlx_delete_image(game->mlx, game->enemy_img[game->enemy_img_i]);
	game->enemy_img[game->enemy_img_i] = NULL;
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
	check_for_hit(game);
	check_for_collectible(game);
}

void	move_player(t_game *game, char c)
{
	static int	counter;
	char		*num;

	if (c == 'A' || c == 'D')
	{
		if (c == 'A')
			game->left_right = 'L';
		else if (c == 'D')
			game->left_right = 'R';
		player_animation(game);
	}
	if ((game->map_x_is_big == 0 && game->map_y_is_big == 0) \
	|| is_close_to_wall(game, c) == 0)
		move_p_img(game, c);
	else
		redraw_map(game, c);
	mlx_delete_image(game->mlx, game->total_moves);
	game->total_moves = NULL;
	num = ft_itoa(++counter);
	if (num == NULL)
		sys_error_exit(game, game->mlx, "Malloc failed");
	game->total_moves = mlx_put_string(game->mlx, num, 190, 0);
	free(num);
	if (game->total_moves == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
}

void	game_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game			*game;
	static double	prev_hammer;
	static int		flag;
	double			time;

	game = param;
	time = mlx_get_time();
	if (flag == 0)
	{
		prev_hammer = time;
		flag = 1;
	}
	if (game->collectible_count > -3)
		check_for_wasdh(game, prev_hammer);
	check_for_esc(keydata, game);
}
