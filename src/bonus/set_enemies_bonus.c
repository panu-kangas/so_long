#include "so_long_bonus.h"

int	check_start_coords(t_game *game, int i, int x, int y)
{
	if (game->enemy_count == 1)
	{
		if (x >= game->player_coord[0] - 1 && x <= game->player_coord[0] + 1 && \
		y >= game->player_coord[1] - 1 && y <= game->player_coord[1] + 1)
			return (1);
		else
			return (0);
	}
	else
	{
		while (--i > -1)
		{
			if (x == game->enemies[i].x && y == game->enemies[i].y)
				return (1);
		}
		if (x >= game->player_coord[0] - 2 && x <= game->player_coord[0] + 2 && \
		y >= game->player_coord[1] - 2 && y <= game->player_coord[1] + 2)
			return (1);
		else
			return (0);
	}
}

int	get_rand_coord(t_game *game, char xy)
{
	int			coord;
	int			max;

	if (xy == 'x')
		max = game->map_width - 1;
	else
		max = game->map_height - 1;
	sranddev();
	coord = rand() % max;
	return (coord);
}

int	get_enemy_count(t_game *game, char c)
{
	int	enemy_count;

	enemy_count = 0;
	if (game->map_width == 3)
		return (0);
	if (c == 'e')
		enemy_count = (game->f_count + game->collectible_count) / 30;
	else if (c == 'h')
		enemy_count = (game->f_count + game->collectible_count) / 20;
	else if (c == 'g')
		enemy_count = (game->f_count + game->collectible_count) / 10;
	if (enemy_count == 0 && game->f_count + game->collectible_count > 8)
		enemy_count++;
	return (enemy_count);
}

int	set_difficulty(t_game *game)
{
	char	buf[2];
	int		bytes;

	start_message();
	while (1)
	{
		bytes = read(0, buf, 2);
		if (bytes == -1)
			sys_error_exit(game, game->mlx, "Read failed");
		else if (bytes == 0 || bytes == 1)
			ft_printf("Please insert only e, h or g and hit enter\n");
		else if (bytes == 2)
		{
			if ((buf[0] == 'e' || buf[0] == 'h' || buf[0] == 'g') \
			&& buf[1] == '\n')
				break ;
			else if (buf[1] != '\n')
			{
				while (buf[0] != '\n')
					read(0, buf, 1);
			}
			ft_printf("Please insert only e, h or g and hit enter\n");
		}
	}
	return (get_enemy_count(game, buf[0]));
}

void	set_enemies(t_game *game)
{
	int		i;
	int		x;
	int		y;

	game->enemy_count = set_difficulty(game);
	game->enemy_img_i = 0;
	game->enemies = malloc(game->enemy_count * sizeof(t_enemy));
	if (game->enemies == NULL)
		sys_error_exit(game, NULL, "Malloc failed");
	i = 0;
	while (i < game->enemy_count)
	{
		x = 0;
		y = 0;
		while (game->map[y][x].type == '1' || game->map[y][x].type == 'P'\
		|| check_start_coords(game, i, x, y) == 1)
		{
			x = get_rand_coord(game, 'x');
			y = get_rand_coord(game, 'y');
		}
		set_enemy_struct(game, i, x, y);
		i++;
	}
}
