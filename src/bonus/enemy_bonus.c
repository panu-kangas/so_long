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
/*	else if (i == 1)
		enemy_text = mlx_load_png("./sprites/animations/enemy2.png");
	else if (i == 2)
		enemy_text = mlx_load_png("./sprites/animations/enemy3.png");
	else if (i == 3)
		enemy_text = mlx_load_png("./sprites/animations/enemy4.png");
	else if (i == 4)
		enemy_text = mlx_load_png("./sprites/animations/enemy5.png");
	else if (i == 5)
		enemy_text = mlx_load_png("./sprites/animations/enemy5.png");	*/
	else
		enemy_text = NULL; //mlx_load_png("./sprites/animations/enemy6.png");
	if (!enemy_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->enemy_img[i] = mlx_texture_to_image(game->mlx, enemy_text);
	if (!game->enemy_img[i])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(enemy_text);
}

void	move_enemy_img(t_game *game, int enemy_x, int enemy_y, int i)
{
	int	start_x;
	int	start_y;
	int	max_w;
	int	max_h;
	int	draw_coord[2];

	start_x = get_x_start(game);
	start_y = get_y_start(game);
	max_w = start_x + game->window_width / 70;
	max_h = start_y + game->window_height / 70;

	if (enemy_x >= start_x && enemy_x < max_w && \
	enemy_y >= start_y && enemy_y < max_h)
	{
		game->enemy_coord[i][4] = game->e_count;
		draw_coord[0] = (enemy_x - start_x) * 70;
		draw_coord[1] = (enemy_y - start_y) * 70;
		if (mlx_image_to_window(game->mlx, game->enemy_img[0], \
		draw_coord[0] + 18, draw_coord[1] + 18) < 0)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		mlx_set_instance_depth(&game->enemy_img[0]->instances[game->e_count++], 4);
	}
}


int	check_other_enemies(t_game *game, int direction, int i)
{
	int	k;
	int	enemy_x;
	int	enemy_y;

	enemy_x = game->enemy_coord[i][0];
	enemy_y = game->enemy_coord[i][1];

	if (direction == 0)
		enemy_y--;
	else if (direction == 1)
		enemy_x++;
	else if (direction == 2)
		enemy_y++;
	else if (direction == 3)
		enemy_x--;

	k = 0;
	while (k < game->enemy_count)
	{
		if (i != k && \
		(game->enemy_coord[k][0] <= enemy_x + 2 && game->enemy_coord[k][0] >= enemy_x - 2) && \
		(game->enemy_coord[k][1] <= enemy_y + 2 && game->enemy_coord[k][1] >= enemy_y - 2))
			return (1);
		k++;
	}
	return (0);
}

int	check_enemy_wall(t_game *game, int direction, int counter, int i)
{
	int			enemy_x;
	int			enemy_y;

	enemy_x = game->enemy_coord[i][0];
	enemy_y = game->enemy_coord[i][1];

	if (direction == 0 && game->map[enemy_y - 1][enemy_x].type == '1')
		return (1);
	else if (direction == 2 && game->map[enemy_y + 1][enemy_x].type == '1')
		return (1);
	else if (direction == 3 && game->map[enemy_y][enemy_x - 1].type == '1')
		return (1);
	else if (direction == 1 && game->map[enemy_y][enemy_x + 1].type == '1')
		return (1);
	
	if (counter == 3)
		return (0);

	if (check_other_enemies(game, direction, i) == 1)
		return (1);
	else
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
		if (game->enemy_coord[i][0] == game->player_coord[0] \
		&& game->enemy_coord[i][1] == game->player_coord[1])
		{
			game->collectible_count = -3;
			write_ending(game, "You lose =(");
			flag = 1;
		}
		i++;
	}
}

void	enemy_movement(t_game *game, int i)
{
	int	direction;
	int	return_direction;
	int	step_count;
	int	counter;

	direction = game->enemy_coord[i][2];
	return_direction = set_return_direction(direction);
	step_count = game->enemy_coord[i][3];
	counter = 0;

	if (step_count == 0 || step_count == -1)
	{
		srand(time(NULL));
		direction = rand() % 4;
		while (1)
		{
			if (check_enemy_wall(game, direction, counter, i) == 0 && direction != return_direction)
				break ;
			direction++;
			counter++;
			if (direction == 4)
				direction = 0;
			if (counter == 4)
			{
				direction = return_direction;
				break ;
			}
		}
		step_count = rand() % 7 + 1;
		return_direction = set_return_direction(direction);
		game->enemy_coord[i][2] = direction;
		game->enemy_coord[i][3] = step_count;
	}

	if (direction == 0)
		game->enemy_coord[i][1] -= 1;
	else if (direction == 2)
		game->enemy_coord[i][1] += 1;
	else if (direction == 3)
		game->enemy_coord[i][0] -= 1;
	else if (direction == 1)
		game->enemy_coord[i][0] += 1;

	game->enemy_coord[i][3]--;

	check_for_hit(game);
	move_enemy_img(game, game->enemy_coord[i][0], game->enemy_coord[i][1], i);

	if (check_enemy_wall(game, direction, counter, i) == 1)
		game->enemy_coord[i][3] = 0;
}


void	enemy_dead_animation(t_game *game, int i)
{
	static int	flag;
	int			draw_coord[2];
	int			instance;

	if (flag == 0)
	{
		instance = game->enemy_coord[i][4];
		game->enemy_img[0]->instances[instance].enabled = 0;
		draw_coord[0] = (game->player_coord[0] - get_x_start(game) + 1) * 70 + 18;
		draw_coord[1] = (game->enemy_coord[i][1] - get_y_start(game)) * 70 + 18;
	}
	else
	{
		draw_coord[0] = game->enemy_dead_img->instances[0].x;
		draw_coord[1] = game->enemy_dead_img->instances[0].y;
		mlx_delete_image(game->mlx, game->enemy_dead_img);
	}
	set_enemy_dead_image(game, flag);


	if (mlx_image_to_window(game->mlx, game->enemy_dead_img, \
	draw_coord[0], draw_coord[1]) < 0)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->enemy_dead_img->instances[0], 4);

	flag++;
	if (flag == 4)
	{
		mlx_delete_image(game->mlx, game->enemy_dead_img);
		game->enemy_coord[i][0] = -2;
		flag = 0;
	}
}


void	enemy_hook(void *param)
{
	t_game			*game;
	static double	prev_time;
	static double	prev_dead_time;
	double			time;
	int				i;

	game = param;
	time = mlx_get_time();
	i = 0;

	if (time > prev_dead_time + 0.15 && game->collectible_count != -3)
	{
		while (i < game->enemy_count)
		{
			if (game->enemy_coord[i][0] == -1)
				enemy_dead_animation(game, i);
			i++;
		}
		i = 0;
		prev_dead_time = time;
	}
	if (time > prev_time + 0.3 && game->collectible_count != -3)
	{
		game->e_count = 0;
		mlx_delete_image(game->mlx, game->enemy_img[0]);
		set_enemy_image(game, 0);

		while (i < game->enemy_count)
		{
			if (game->enemy_coord[i][0] >= 0)
				enemy_movement(game, i);
			i++;
		}
		prev_time = time;
	}
}