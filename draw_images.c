#include "so_long.h"

void	check_map_type(t_game *game, int x, int y)
{
	if (x == game->player_coord[0] && y == game->player_coord[1])
	{
		if (x == game->exit_coord[0] && y == game->exit_coord[1])
			draw_exit(game, game->draw_coord);
		else
			draw_floor(game, game->draw_coord);
		draw_player(game, game->draw_coord);
	}
	else if (game->map[y][x].type == '0' || game->map[y][x].type == 'P')
		draw_floor(game, game->draw_coord);
	else if (game->map[y][x].type == '1')
		draw_wall(game, game->draw_coord);
	else if (game->map[y][x].type == 'C')
		draw_collectible(game, x, y, game->draw_coord);
	else if (game->map[y][x].type == 'E')
		draw_exit(game, game->draw_coord);
}

int	get_y_start(t_game *game)
{
	int	height;
	int	dist_to_walls;

	if (game->map_is_big == 0)
		return (0);
	if (game->player_coord[1] <= 3)
		return (0);
	height = game->window_height / 70;
	dist_to_walls = game->map_height - game->player_coord[1] - 1;
	if (dist_to_walls <= 4)
		return (game->player_coord[1] - (height / 2) - (4 - dist_to_walls));
	else
		return (game->player_coord[1] - (height / 2) + 1);
}

int	get_x_start(t_game *game)
{
	int	width;
	int	dist_to_walls;

	if (game->map_is_big == 0)
		return (0);
	if (game->player_coord[0] <= 6)
		return (0);
	width = game->window_width / 70;
	dist_to_walls = game->map_width - game->player_coord[0] - 1;
	if (dist_to_walls <= 7)
		return (game->player_coord[0] - (width / 2) - (7 - dist_to_walls));
	else
		return (game->player_coord[0] - (width / 2));
}

void	draw_images(t_game *game)
{
	int	x;
	int	y;
	int	width;
	int	height;

	game->f_count = 0;
	game->w_count = 0;
	game->c_count = 0;
	width = game->window_width / 70;
	height = game->window_height / 70;
	y = get_y_start(game);
	while (game->draw_coord[1] < height * 70)
	{
		x = get_x_start(game);
		game->draw_coord[0] = 0;
		while (game->draw_coord[0] < width * 70)
		{
			check_map_type(game, x, y);
			game->draw_coord[0] += 70;
			x++;
		}
		game->draw_coord[1] += 70;
		y++;
	}
}
