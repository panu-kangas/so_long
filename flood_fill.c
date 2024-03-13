#include "so_long.h"

void	check_path_collectible(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_line_count)
	{
		x = 0;
		while (x < game->map_line_len)
		{
			if (game->map[y][x].type == 'C')
			{
				if (game->map[y][x].flood_fill == 0)
					break ;
			}
			x++;
		}
		if (x != game->map_line_len)
			break ;
		y++;
	}
	if (y != game->map_line_count)
		write_error(game, NULL, "Invalid map; Collectible(s) unreachable");
}

void	check_path_exit(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_line_count)
	{
		x = 0;
		while (x < game->map_line_len)
		{
			if (game->map[y][x].type == 'E')
				break ;
			x++;
		}
		if (x != game->map_line_len)
			break ;
		y++;
	}
	if (game->map[y][x].flood_fill == 0)
		write_error(game, NULL, "Invalid map; Player can't reach Exit");
}

void	make_fill(t_game *game, int x, int y)
{
	int line_count;
	int line_len;

	line_count = game->map_line_count;
	line_len = game->map_line_len;
	if (y > 0 && game->map[y - 1][x].flood_fill == 0)
	{
		game->map[y - 1][x].flood_fill = 1;
		make_fill(game, x, y - 1);
	}
	if (y < (line_count - 1) && game->map[y + 1][x].flood_fill == 0)
	{
		game->map[y + 1][x].flood_fill = 1;
		make_fill(game, x, y + 1);
	}
	if (x > 0 && game->map[y][x - 1].flood_fill == 0)
	{
		game->map[y][x - 1].flood_fill = 1;
		make_fill(game, x - 1, y);
	}
	if (x < (line_len - 1) && game->map[y][x + 1].flood_fill == 0)
	{
		game->map[y][x + 1].flood_fill = 1;
		make_fill(game, x + 1, y);
	}
}

void	init_fill(t_game *game)
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
				game->map[y][x].flood_fill = -1;
			else
				game->map[y][x].flood_fill = 0;
			x++;
		}
		y++;
	}
}

void	flood_fill(t_game *game)
{
	int	x;
	int	y;

	init_fill(game);
	y = 0;
	while (y < game->map_line_count)
	{
		x = 0;
		while (x < game->map_line_len)
		{
			if (game->map[y][x].type == 'P')
				break ;
			x++;
		}
		if (x != game->map_line_len)
			break ;
		y++;
	}
	make_fill(game, x, y);
	check_path_exit(game);
	check_path_collectible(game);

	
}