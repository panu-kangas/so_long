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
		game->enemies[i].instance = game->e_count;
		draw_coord[0] = (enemy_x - start_x) * 70;
		draw_coord[1] = (enemy_y - start_y) * 70;
		if (mlx_image_to_window(game->mlx, game->enemy_img[game->enemy_img_i], \
		draw_coord[0] + 18, draw_coord[1] + 18) < 0)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		mlx_set_instance_depth(&game->enemy_img[game->enemy_img_i]->instances[game->e_count++], 4);
	}
}


int	check_other_enemies(t_game *game, int direction, int i)
{
	int	k;
	int	enemy_x;
	int	enemy_y;

	enemy_x = game->enemies[i].x;
	enemy_y = game->enemies[i].y;

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
		(game->enemies[k].x <= enemy_x + 2 && game->enemies[k].x >= enemy_x - 2) && \
		(game->enemies[k].y <= enemy_y + 2 && game->enemies[k].y >= enemy_y - 2))
			return (1);
		k++;
	}
	return (0);
}

int	check_enemy_wall(t_game *game, int direction, int counter, int i)
{
	int			enemy_x;
	int			enemy_y;

	enemy_x = game->enemies[i].x;
	enemy_y = game->enemies[i].y;

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

void	enemy_movement(t_game *game, int i)
{
	int	direction;
	int	return_direction;
	int	step_count;
	int	counter;

	direction = game->enemies[i].direction;
	return_direction = set_return_direction(direction);
	step_count = game->enemies[i].step_count;
	counter = 0;

	if (step_count == 0 || step_count == -1)
	{
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
		game->enemies[i].direction = direction;
		game->enemies[i].step_count = step_count;
	}

	if (direction == 0)
		game->enemies[i].y -= 1;
	else if (direction == 2)
		game->enemies[i].y += 1;
	else if (direction == 3)
		game->enemies[i].x -= 1;
	else if (direction == 1)
		game->enemies[i].x += 1;

	game->enemies[i].step_count--;

	check_for_hit(game);
	move_enemy_img(game, game->enemies[i].x, game->enemies[i].y, i);

	if (check_enemy_wall(game, direction, counter, i) == 1)
		game->enemies[i].step_count = 0;
}


void	enemy_dead_animation(t_game *game, int i)
{
	static int	flag;
	int	draw_coord[2];

	draw_coord[0] = (game->enemies[i].x - get_x_start(game)) * 70 + 18;
	draw_coord[1] = (game->enemies[i].y - get_y_start(game)) * 70 + 18;
	if (flag > 0)
		mlx_delete_image(game->mlx, game->enemy_dead_img);
	set_enemy_dead_image(game, flag);


	if (mlx_image_to_window(game->mlx, game->enemy_dead_img, \
	draw_coord[0], draw_coord[1]) < 0)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->enemy_dead_img->instances[0], 4);

	flag++;
	if (flag == 4)
	{
		mlx_delete_image(game->mlx, game->enemy_dead_img);
		game->enemies[i].is_dead = 1;
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

	if (time > prev_dead_time + 0.2 && game->collectible_count > -3)
	{
		while (i < game->enemy_count)
		{
			if (game->enemies[i].is_dying == 1 && game->enemies[i].is_dead == 0)
				enemy_dead_animation(game, i);
			i++;
		}
		i = 0;
		prev_dead_time = time;
	}
	if (time > prev_time + 0.4 && game->collectible_count > -3)
	{
		game->e_count = 0;
		mlx_delete_image(game->mlx, game->enemy_img[game->enemy_img_i]);
	//	game->enemy_img_i += 1; --> SHOULD I REMOVE ANIMATION ?!
		if (game->enemy_img_i == 6)
			game->enemy_img_i = 0; 
		set_enemy_image(game, game->enemy_img_i);

		while (i < game->enemy_count)
		{
			if (game->enemies[i].is_dying == 0)
				enemy_movement(game, i);
			i++;
		}
		prev_time = time;
	}
}