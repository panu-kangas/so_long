#include "so_long.h"

void	set_instances(t_game *game)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (y < game->map_line_count)
	{
		x = 0;
		while (x < game->map_line_len)
		{
			if (game->map[y][x].type == 'C')
				game->map[y][x].instance = &game->collectible_img->instances[i++];
			x++;
		}
		y++;
	}
}

void	set_img_depth(t_game *game, mlx_image_t *img, int count, int num)
{
	int	i;

	i = -1;
	if (num == 1)
	{
		while (++i < count)
			mlx_set_instance_depth(&img->instances[i], 0); // does this need error check ?
	}
	else if (num == 2)
	{
		while (++i < count)
			mlx_set_instance_depth(&img->instances[i], 0); // does this need error check ?
	}
	else if (num == 3)
	{
		game->collectible_count = count;
		while (++i < count)
			mlx_set_instance_depth(&img->instances[i], 1); // does this need error check ?
	}
	else if (num == 4)
	{
		while (++i < count)
			mlx_set_instance_depth(&img->instances[i], 2); // does this need error check ?
	}
}

void	draw_exit(t_game *game, int x, int y)
{
	mlx_texture_t	*exit_text;
	mlx_image_t		*exit_img;

	exit_text = mlx_load_png("./tiles/exit.png");
	if (!exit_text)
        return ; // error_exit_MLX
	exit_img = mlx_texture_to_image(game->mlx, exit_text);
	if (!exit_img)
        return ; // error_exit_MLX
	while (y < game->map_line_count)
	{
		x = 0;
		while (x < game->map_line_len)
		{
			if (game->map[y][x].type == 'E')
			{
				if (mlx_image_to_window(game->mlx, exit_img, x * 70, y * 70) < 0)
        			return ; // error_exit_MLX
			}
			x++;
		}
		y++;
	}
	set_img_depth(game, exit_img, 1, 1);
	game->exit_img = exit_img;
}

void	draw_player(t_game *game, int x, int y)
{
	mlx_texture_t	*player_text;
	mlx_image_t		*player_img;

	player_text = mlx_load_png("./sprites/player.png");
	if (!player_text)
        return ; // error_exit_MLX
	player_img = mlx_texture_to_image(game->mlx, player_text);
	if (!player_img)
        return ; // error_exit_MLX
	while (y < game->map_line_count)
	{
		x = 0;
		while (x < game->map_line_len)
		{
			if (game->map[y][x].type == 'P')
			{
				if (mlx_image_to_window(game->mlx, player_img, x * 70, y * 70) < 0)
        			return ; // error_exit_MLX
			}
			x++;
		}
		y++;
	}
	set_img_depth(game, player_img, 1, 4);
	game->player_img = player_img;
}

void	draw_collectible(t_game *game, int collectible_count, int x, int y)
{
	mlx_texture_t	*collectible_text;
	mlx_image_t		*collectible_img;

	collectible_text = mlx_load_png("./sprites/collectible.png");
	if (!collectible_text)
        return ; // error_exit_MLX
	collectible_img = mlx_texture_to_image(game->mlx, collectible_text);
	if (!collectible_img)
        return ; // error_exit_MLX
	y = -1;
	while (++y < game->map_line_count)
	{
		x = -1;
		while (++x < game->map_line_len)
		{
			if (game->map[y][x].type == 'C')
			{
				if (mlx_image_to_window(game->mlx, collectible_img, (x * 70) + 17, (y * 70) + 22) < 0) // should I count exact centre?
        			return ; // error_exit_MLX
				collectible_count++;
			}
		}
	}
	game->collectible_img = collectible_img; 
	set_img_depth(game, collectible_img, collectible_count, 3);
}

void	draw_wall(t_game *game, int wall_count, int x, int y)
{
	mlx_texture_t	*wall_text;
	mlx_image_t		*wall_img;

	wall_text = mlx_load_png("./tiles/wall.png");
	if (!wall_text)
        return ; // error_exit_MLX
	wall_img = mlx_texture_to_image(game->mlx, wall_text);
	if (!wall_img)
        return ; // error_exit_MLX
	y = -1;
	while (++y < game->map_line_count)
	{
		x = -1;
		while (++x < game->map_line_len)
		{
			if (game->map[y][x].type == '1')
			{
				if (mlx_image_to_window(game->mlx, wall_img, x * 70, y * 70) < 0)
        			return ; // error_exit_MLX
				wall_count++;
			}
		}
	}
	set_img_depth(game, wall_img, wall_count, 2);
}

void	draw_floor(t_game *game, int floor_count, int x, int y)
{
	mlx_texture_t	*floor_text;
	mlx_image_t		*floor_img;

	floor_text = mlx_load_png("./tiles/floor.png");
	if (!floor_text)
        return ; // error_exit_MLX
	floor_img = mlx_texture_to_image(game->mlx, floor_text);
	if (!floor_img)
        return ; // error_exit_MLX
	y = -1;
	while (++y < game->map_line_count)
	{
		x = -1;
		while (++x < game->map_line_len)
		{
			if (game->map[y][x].type == '0' || game->map[y][x].type == 'P' || \
			game->map[y][x].type == 'C')
			{
				if (mlx_image_to_window(game->mlx, floor_img, x * 70, y * 70) < 0)
        			return ; // error_exit_MLX
				floor_count++;
			}
		}
	}
	set_img_depth(game, floor_img, floor_count, 1);
}

void	draw_all(t_game *game)
{
	draw_floor(game, 0, 0, 0);
	draw_wall(game, 0, 0, 0);
	draw_collectible(game, 0, 0, 0);
	draw_player(game, 0, 0);
	draw_exit(game, 0, 0);
	set_instances(game);
}