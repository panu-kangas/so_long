#include "so_long.h"

int	check_dist(t_game *game, int x, int y, int count)
{
	if (game->map[y][x].dist_to_player == 0)
		return (0);
	if (game->map[y][x].dist_to_player >= count)
		return (0);
	return (1);
}

void	get_dist(t_game *game, int x, int y, int count)
{
	int line_count;
	int line_len;

	line_count = game->map_line_count;
	line_len = game->map_line_len;
	if (y > 0 && check_dist(game, x, y - 1, count) == 0)
	{
		game->map[y - 1][x].dist_to_player = count + 1;
		get_dist(game, x, y - 1, count + 1);
	}
	if (y < (line_count - 1) && check_dist(game, x, y + 1, count) == 0)
	{
		game->map[y + 1][x].dist_to_player = count + 1;
		get_dist(game, x, y + 1, count + 1);
	}
	if (x > 0 && check_dist(game, x - 1, y, count) == 0)
	{
		game->map[y][x - 1].dist_to_player = count + 1;
		get_dist(game, x - 1, y, count + 1);
	}
	if (x < (line_len - 1) && check_dist(game, x + 1, y, count) == 0)
	{
		game->map[y][x + 1].dist_to_player = count + 1;
		get_dist(game, x + 1, y, count + 1);
	}
}

void	init_dist(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_line_count)
	{
		x = 0;
		while (x < game->map_line_len)
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
	get_dist(game, x, y, 0);
}
