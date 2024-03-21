#include "so_long_bonus.h"

void	mark_dist(t_game *game, int x, int y, int i)
{
	if (game->map[y][x].dist_to_player == i)
	{
		if (game->map[y + 1][x].dist_to_player == 0)
			game->map[y + 1][x].dist_to_player = i + 1;
		if (game->map[y - 1][x].dist_to_player == 0)
			game->map[y - 1][x].dist_to_player = i + 1;
		if (game->map[y][x + 1].dist_to_player == 0)
			game->map[y][x + 1].dist_to_player = i + 1;
		if (game->map[y][x - 1].dist_to_player == 0)
			game->map[y][x - 1].dist_to_player = i + 1;
	}
}

void	loop_map(t_game *game, int x, int y, int i)
{
	int			orig_x;
	int			orig_y;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	orig_x = x;
	orig_y = y;
	while (y < orig_y + (1 + (2 * i)))
	{
		x = orig_x;
		while (x < orig_x + (1 + (2 * i)))
		{
			if (game->map[y][x].dist_to_player != -1)
				mark_dist(game, x, y, i);
			if (x == game->map_width - 1)
				break ;
			x++;
		}
		if (y == game->map_height - 1)
			break ;
		y++;
	}
}

void	get_dist(t_game *game, int x, int y)
{
	int	i;
	int	exit_x;
	int	exit_y;

	if (game->map[y + 1][x].dist_to_player != -1)
		game->map[y + 1][x].dist_to_player = 1;
	if (game->map[y - 1][x].dist_to_player != -1)
		game->map[y - 1][x].dist_to_player = 1;
	if (game->map[y][x + 1].dist_to_player != -1)
		game->map[y][x + 1].dist_to_player = 1;
	if (game->map[y][x - 1].dist_to_player != -1)
		game->map[y][x - 1].dist_to_player = 1;
	exit_x = game->exit_co[0];
	exit_y = game->exit_co[1];
	i = 1;
	while (game->map[exit_y][exit_x].dist_to_player == 0)
	{
		loop_map(game, (x - i), (y - i), i);
		i++;
	}
}

void	init_dist(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x].type == '1')
				game->map[y][x].dist_to_player = -1;
			else
				game->map[y][x].dist_to_player = 0;
			x++;
		}
		y++;
	}
}

void	get_dist_to_player(t_game *game)
{
	int	x;
	int	y;

	x = game->player_coord[0];
	y = game->player_coord[1];
	init_dist(game);
	get_dist(game, x, y);
}
