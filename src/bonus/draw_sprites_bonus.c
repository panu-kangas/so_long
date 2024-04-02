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
	int	i;

	i = game->collectible_img_i;
	draw_floor(game, draw_coord);
	c_count = game->c_count;
	if (mlx_image_to_window(game->mlx, game->collectible_img[i], \
	draw_coord[0] + 24, draw_coord[1] + 27) < 0)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->collectible_img[i]->instances[c_count], 1);
	game->map[y][x].c_instance = c_count;
	game->c_count++;
}

void	draw_enemy(t_game *game, int x, int y, int *draw_coord)
{
	int	e_count;
	int	i;

	i = game->enemy_img_i;
	e_count = game->e_count;
	if (mlx_image_to_window(game->mlx, game->enemy_img[i], \
	draw_coord[0] + 18, draw_coord[1] + 18) < 0)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->enemy_img[i]->instances[e_count], 4);
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
			break;
		i++;
	}
	game->enemies[i].instance = e_count;
	game->e_count++;
}
