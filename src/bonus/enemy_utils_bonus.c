#include "so_long_bonus.h"

void	set_enemy_dead_image(t_game *game, int k)
{
	mlx_texture_t	*enemy_text;

	if (k == 0)
		enemy_text = mlx_load_png("./sprites/animations/enemy_dead1.png");
	else if (k == 1)
		enemy_text = mlx_load_png("./sprites/animations/enemy_dead2.png");
	else if (k == 2)
		enemy_text = mlx_load_png("./sprites/animations/enemy_dead3.png");
	else
		enemy_text = mlx_load_png("./sprites/animations/enemy_dead4.png");
	if (!enemy_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->enemy_dead_img = mlx_texture_to_image(game->mlx, enemy_text);
	if (!game->enemy_dead_img)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(enemy_text);
}

void	set_enemy_image(t_game *game, int i)
{
	mlx_texture_t	*enemy_text;

	if (i == 0)
		enemy_text = mlx_load_png("./sprites/animations/enemy1.png");
	else if (i == 1)
		enemy_text = mlx_load_png("./sprites/animations/enemy2.png");
	else if (i == 2)
		enemy_text = mlx_load_png("./sprites/animations/enemy3.png");
	else if (i == 3)
		enemy_text = mlx_load_png("./sprites/animations/enemy4.png");
	else if (i == 4)
		enemy_text = mlx_load_png("./sprites/animations/enemy5.png");
	else
		enemy_text = mlx_load_png("./sprites/animations/enemy6.png");
	if (!enemy_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->enemy_img[i] = mlx_texture_to_image(game->mlx, enemy_text);
	if (!game->enemy_img[i])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(enemy_text);
}

int	check_other_enemies(t_game *game, int direction, int i)
{
	int	k;
	int	pig_x;
	int	pig_y;

	pig_x = game->enemies[i].x;
	pig_y = game->enemies[i].y;
	if (direction == 0)
		pig_y--;
	else if (direction == 1)
		pig_x++;
	else if (direction == 2)
		pig_y++;
	else if (direction == 3)
		pig_x--;
	k = 0;
	while (k < game->enemy_count)
	{
		if (i != k && \
		(game->enemies[k].x <= pig_x + 1 && game->enemies[k].x >= pig_x - 1) \
		&& \
		(game->enemies[k].y <= pig_y + 1 && game->enemies[k].y >= pig_y - 1))
			return (1);
		k++;
	}
	return (0);
}

int	set_return_direction(int direction)
{
	if (direction == 0)
		return (2);
	else if (direction == 1)
		return (3);
	else if (direction == 2)
		return (0);
	else if (direction == 3)
		return (1);
	else
		return (-1);
}

void	check_for_hit(t_game *game)
{
	int			i;
	static int	flag;

	i = 0;
	while (flag == 0 && i < game->enemy_count)
	{
		if (game->enemies[i].x == game->player_coord[0] \
		&& game->enemies[i].y == game->player_coord[1])
		{
			if (game->enemies[i].is_dying == 0)
			{
				game->collectible_count = -3;
				write_ending(game, "You lose =(");
				flag = 1;
			}
		}
		i++;
	}
}
