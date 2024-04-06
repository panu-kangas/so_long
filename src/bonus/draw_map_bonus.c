#include "so_long_bonus.h"

void	get_sprite_images(t_game *game, int flag)
{
	mlx_texture_t	*player_text;
	int				i_c;
	int				i_e;

	i_c = game->collectible_img_i;
	i_e = game->enemy_img_i;
	if (flag == 0)
	{
		player_text = mlx_load_png("./sprites/animations/player1.png");
		if (!player_text)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		game->player_img[0] = mlx_texture_to_image(game->mlx, player_text);
		if (!game->player_img[0])
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		mlx_delete_texture(player_text);
	}
	set_collectible_image(game, i_c);
	set_enemy_image(game, i_e);
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

void	draw_background(t_game *game)
{
	mlx_image_t	*background_up;
	uint32_t	x;
	uint32_t	y;

	background_up = mlx_new_image(game->mlx, 240, 20);
	y = 0;
	while (y < background_up->height)
	{
		x = 0;
		while (x < background_up->width)
		{
			mlx_put_pixel(background_up, x, y, ft_pixel(196, 107, 65, 255));
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, background_up, 0, 0);
	mlx_set_instance_depth(&background_up->instances[0], 5);
	game->background_up_img = background_up;
}

void	draw_map(t_game *game, int flag)
{
	get_tile_images(game);
	get_sprite_images(game, flag);
	draw_background(game);
	draw_images(game, flag);
	game->draw_coord[0] = 0;
	game->draw_coord[1] = 0;
}
