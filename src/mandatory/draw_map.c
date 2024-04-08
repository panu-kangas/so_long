/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:27:20 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:27:21 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_sprite_images(t_game *game)
{
	mlx_texture_t	*player_text;
	mlx_texture_t	*collectible_text;

	player_text = mlx_load_png("./sprites/player.png");
	if (!player_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->player_img = mlx_texture_to_image(game->mlx, player_text);
	if (!game->player_img)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(player_text);
	collectible_text = mlx_load_png("./sprites/collectible.png");
	if (!collectible_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->collectible_img = mlx_texture_to_image(game->mlx, collectible_text);
	if (!game->collectible_img)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(collectible_text);
}

void	get_exit_img(t_game *game)
{
	mlx_texture_t	*exit1_text;
	mlx_texture_t	*exit2_text;

	exit1_text = mlx_load_png("./tiles/exit1.png");
	if (!exit1_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->exit_img[0] = mlx_texture_to_image(game->mlx, exit1_text);
	if (!game->exit_img[0])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(exit1_text);
	exit2_text = mlx_load_png("./tiles/exit2.png");
	if (!exit2_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->exit_img[1] = mlx_texture_to_image(game->mlx, exit2_text);
	if (!game->exit_img[1])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(exit2_text);
}

void	get_tile_images(t_game *game)
{
	mlx_texture_t	*floor_text;
	mlx_texture_t	*wall_text;

	floor_text = mlx_load_png("./tiles/floor.png");
	if (!floor_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->floor_img = mlx_texture_to_image(game->mlx, floor_text);
	if (!game->floor_img)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(floor_text);
	wall_text = mlx_load_png("./tiles/wall.png");
	if (!wall_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->wall_img = mlx_texture_to_image(game->mlx, wall_text);
	if (!game->wall_img)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(wall_text);
	get_exit_img(game);
}

void	draw_map(t_game *game)
{
	get_tile_images(game);
	get_sprite_images(game);
	draw_images(game);
	game->draw_coord[0] = 0;
	game->draw_coord[1] = 0;
}
