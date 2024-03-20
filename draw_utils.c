#include "so_long.h"

void	draw_floor(t_game *game, int *draw_coord)
{
	int	f_count;

	f_count = game->f_count;
	if (mlx_image_to_window(game->mlx, game->floor_img, draw_coord[0], draw_coord[1]) < 0)
    	error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->floor_img->instances[f_count], 0);
	game->f_count++;
}

void	draw_wall(t_game *game, int *draw_coord)
{
	int	w_count;

	w_count = game->w_count;
	if (mlx_image_to_window(game->mlx, game->wall_img, draw_coord[0], draw_coord[1]) < 0)
    	error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->wall_img->instances[w_count], 0);
	game->w_count++;
}

void	draw_player(t_game *game, int *draw_coord)
{
	if (mlx_image_to_window(game->mlx, game->player_img, draw_coord[0], draw_coord[1]) < 0)
    	error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->player_img->instances[0], 3);
}

void	draw_collectible(t_game *game, int x, int y, int *draw_coord)
{
	int	c_count;

	draw_floor(game, draw_coord);
	c_count = game->c_count;
	if (mlx_image_to_window(game->mlx, game->collectible_img, draw_coord[0] + 17, draw_coord[1] + 22) < 0)
    	error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->collectible_img->instances[c_count], 1);
	game->map[y][x].c_instance = c_count;
	game->c_count++;
}

void	draw_exit(t_game *game, int *draw_coord)
{
	if (game->map_is_big == 0)
	{
		if (mlx_image_to_window(game->mlx, game->exit_img[0], draw_coord[0], draw_coord[1]) < 0)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		if (mlx_image_to_window(game->mlx, game->exit_img[1], draw_coord[0], draw_coord[1]) < 0)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		mlx_set_instance_depth(&game->exit_img[0]->instances[0], 1);
		mlx_set_instance_depth(&game->exit_img[1]->instances[0], 0);
	}
	else
	{
		if (game->collectible_count > 0)
		{
			if (mlx_image_to_window(game->mlx, game->exit_img[0], draw_coord[0], draw_coord[1]) < 0)
				error_exit(game, game->mlx, mlx_strerror(mlx_errno));
			mlx_set_instance_depth(&game->exit_img[0]->instances[0], 0);
		}
		else
		{
			if (mlx_image_to_window(game->mlx, game->exit_img[1], draw_coord[0], draw_coord[1]) < 0)
				error_exit(game, game->mlx, mlx_strerror(mlx_errno));
			mlx_set_instance_depth(&game->exit_img[1]->instances[0], 0);
		}
	}
}