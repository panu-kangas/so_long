#include "so_long_bonus.h"

void	enemy_dead_animation(t_game *game, int i)
{
	static int	flag;
	int			draw_coord[2];

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

void	enemy_animation(t_game *game)
{
	int	i;

	i = 0;
	game->e_count = 0;
	mlx_delete_image(game->mlx, game->enemy_img[game->enemy_img_i]);
	game->enemy_img_i += 1;
	if (game->enemy_img_i == 6)
		game->enemy_img_i = 0;
	set_enemy_image(game, game->enemy_img_i);
	while (i < game->enemy_count)
	{
		if (game->enemies[i].is_dying == 0)
			enemy_movement(game, i);
		i++;
	}
}

void	e_img_draw(t_game *game, int enemy_x, int enemy_y, int i)
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
		mlx_set_instance_depth(\
		&game->enemy_img[game->enemy_img_i]->instances[game->e_count++], 4);
	}
}

void	new_enemy_img(t_game *game)
{
	static int	flag;
	int			i;

	if (flag % 2 == 0)
	{
		i = 0;
		game->e_count = 0;
		mlx_delete_image(game->mlx, game->enemy_img[game->enemy_img_i]);
		game->enemy_img_i += 1;
		if (game->enemy_img_i == 6)
			game->enemy_img_i = 0;
		set_enemy_image(game, game->enemy_img_i);
		while (i < game->enemy_count)
		{
			if (game->enemies[i].is_dying == 0)
				e_img_draw(game, game->enemies[i].x, game->enemies[i].y, i);
			i++;
		}
	}
	flag++;
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
		new_enemy_img(game);
		while (i < game->enemy_count)
		{
			if (game->enemies[i].is_dying == 1 && game->enemies[i].is_dead == 0)
				enemy_dead_animation(game, i);
			i++;
		}
		prev_dead_time = time;
	}
	if (time > prev_time + 0.4 && game->collectible_count > -3)
	{
		enemy_animation(game);
		prev_time = time;
	}
}
