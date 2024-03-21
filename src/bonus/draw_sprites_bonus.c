#include "so_long_bonus.h"

void	draw_player(t_game *game, int *draw_coord)
{
	if (mlx_image_to_window(game->mlx, game->player_img[0], \
	draw_coord[0], draw_coord[1] - 10) < 0)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->player_img[0]->instances[0], 3);
}

void	draw_collectible(t_game *game, int x, int y, int *draw_coord)
{
	int	c_count;

	draw_floor(game, draw_coord);
	c_count = game->c_count;
	if (mlx_image_to_window(game->mlx, game->collectible_img, \
	draw_coord[0] + 17, draw_coord[1] + 22) < 0)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->collectible_img->instances[c_count], 1);
	game->map[y][x].c_instance = c_count;
	game->c_count++;
}
