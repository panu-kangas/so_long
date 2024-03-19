#include "so_long.h"

void		mark_map(t_game *game, int x, int y, char c)
{
	if (c == '0')
		game->map[y][x].type = '0';
	else if (c == '1')
		game->map[y][x].type = '1';
	else if (c == 'C')
		game->map[y][x].type = 'C';
	else if (c == 'E')
	{
		game->map[y][x].type = 'E';
		game->exit_coord[0] = x;
		game->exit_coord[1] = y;
	}
	else if (c == 'P')
	{
		game->map[y][x].type = 'P';
		game->player_coord[0] = x;
		game->player_coord[1] = y;
	}
}

void	allocate_map(t_game *game, int line_count, int line_len)
{
	int	i;

	game->map = malloc(line_count * sizeof(t_map *));
	if (game->map == NULL)
		sys_error_exit(game, NULL, "Malloc failed");
	i = 0;
	while (i < line_count)
	{
		game->map[i] = malloc(line_len * sizeof(t_map));
		if (game->map[i] == NULL)
			sys_error_exit(game, NULL, "Malloc failed");
		i++;
	}
}

void	set_map(t_game *game, char *map_file_str, int line_count, int line_len)
{
	int	i;
	int	x;
	int	y;

	allocate_map(game, line_count, line_len);
	i = 0;
	y = 0;
	while (y < line_count)
	{
		x = 0;
		while (x < line_len)
		{
			mark_map(game, x, y, map_file_str[i]);
			i++;
			x++;
		}
		i++;
		y++;
	}
}

void	parse_map(t_game *game)
{
	int		line_count;
	int		line_len;
	int		i;

	game->map_file_str = get_map_str(game);
	if (game->map_file_str == NULL)
		error_exit(game, NULL, "Map-file is empty"); 

	line_count = validate_map(game, game->map_file_str);

	
	i = 0;
	while (game->map_file_str[i] != '\n')
		i++;
	line_len = i;

	game->map_height = line_count;
	game->map_width = line_len;
	
	set_map(game, game->map_file_str, line_count, line_len);
	flood_fill(game);
}