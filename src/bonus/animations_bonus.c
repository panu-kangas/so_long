/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:31:19 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:31:21 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	set_player_image_left(t_game *game, int i)
{
	mlx_texture_t	*player_text;

	if (i == 0)
		player_text = mlx_load_png("./sprites/animations/player1_mirror.png");
	else if (i == 1)
		player_text = mlx_load_png("./sprites/animations/player2_mirror.png");
	else if (i == 2)
		player_text = mlx_load_png("./sprites/animations/player3_mirror.png");
	else if (i == 3)
		player_text = mlx_load_png("./sprites/animations/player4_mirror.png");
	else if (i == 4)
		player_text = mlx_load_png("./sprites/animations/player5_mirror.png");
	else if (i == 5)
		player_text = mlx_load_png("./sprites/animations/player6_mirror.png");
	else
		player_text = mlx_load_png("./sprites/animations/player7_mirror.png");
	if (!player_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->player_img[i] = mlx_texture_to_image(game->mlx, player_text);
	if (!game->player_img[i])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(player_text);
	game->player_img_i = i;
}

void	set_player_image_right(t_game *game, int i)
{
	mlx_texture_t	*player_text;

	if (i == 0)
		player_text = mlx_load_png("./sprites/animations/player1.png");
	else if (i == 1)
		player_text = mlx_load_png("./sprites/animations/player2.png");
	else if (i == 2)
		player_text = mlx_load_png("./sprites/animations/player3.png");
	else if (i == 3)
		player_text = mlx_load_png("./sprites/animations/player4.png");
	else if (i == 4)
		player_text = mlx_load_png("./sprites/animations/player5.png");
	else if (i == 5)
		player_text = mlx_load_png("./sprites/animations/player6.png");
	else
		player_text = mlx_load_png("./sprites/animations/player7.png");
	if (!player_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->player_img[i] = mlx_texture_to_image(game->mlx, player_text);
	if (!game->player_img[i])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(player_text);
	game->player_img_i = i;
}

void	player_animation(t_game *game)
{
	static int	i;
	int			k;
	int			x;
	int			y;

	x = game->player_img[i]->instances[0].x;
	y = game->player_img[i]->instances[0].y;
	mlx_delete_image(game->mlx, game->player_img[i]);
	game->player_img[i] = NULL;
	if (i == 6)
		k = 0;
	else
		k = i + 1;
	if (game->left_right == 'R')
		set_player_image_right(game, k);
	else
		set_player_image_left(game, k);
	if (mlx_image_to_window(game->mlx, game->player_img[k], \
	x, y) < 0)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->player_img[k]->instances[0], 3);
	i++;
	if (i == 7)
		i = 0;
}

void	animation_hook(void *param)
{
	t_game			*game;
	static double	prev_time;
	static double	prev_hammer_time;
	double			time;

	game = param;
	time = mlx_get_time();
	if (time > prev_hammer_time + 0.075 && game->collectible_count > -3)
	{
		if (game->attack == 1)
			attack_animation(game);
		prev_hammer_time = time ;
	}
	if (time > prev_time + 0.15 && game->collectible_count > -3 \
	&& game->attack == 0)
	{
		if (game->attack == 0)
			player_animation(game);
		collectible_animation(game);
		prev_time = time;
	}
}
