#include "so_long_bonus.h"

void	attack_animation(t_game *game)
{
	mlx_texture_t	*attack_text[2];
	int			x;
	int			y;
	int			i;
	static int	flag;

	i = game->player_img_i;
	x = game->player_img[i]->instances[0].x;
	y = game->player_img[i]->instances[0].y;

	attack_text[0] = mlx_load_png("./sprites/animations/attack1.png");
	if (!attack_text[0])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	attack_text[1] = mlx_load_png("./sprites/animations/attack2.png");
	if (!attack_text[1])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));

	if (flag == 0)
	{
		game->attack_img[0] = mlx_texture_to_image(game->mlx, attack_text[0]);
		if (!game->attack_img[0])
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		game->attack_img[1] = mlx_texture_to_image(game->mlx, attack_text[1]);
		if (!game->attack_img[1])
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		mlx_delete_texture(attack_text[0]);
		mlx_delete_texture(attack_text[1]);
	}

	if (flag == 0)
	{
		game->player_img[game->player_img_i]->enabled = 0;
		if (mlx_image_to_window(game->mlx, game->attack_img[0], \
		x, y) < 0)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		mlx_set_instance_depth(&game->attack_img[0]->instances[0], 4);
		flag = 1;
	}
	else if (flag == 1)
	{
		mlx_delete_image(game->mlx, game->attack_img[0]);
		if (mlx_image_to_window(game->mlx, game->attack_img[1], \
		x, y) < 0)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		mlx_set_instance_depth(&game->attack_img[1]->instances[0], 4);
		flag = 2;
	}
	else
	{
		mlx_delete_image(game->mlx, game->attack_img[1]);
		game->player_img[game->player_img_i]->enabled = 1;
		game->attack = 0;
		flag = 0;
	}
}

void	set_player_image(t_game *game, int i)
{
	mlx_texture_t	*player_text;
	
	if (i == 0)
		player_text = mlx_load_png("./sprites/animations/player1.png");
	else if (i == 1)
		player_text = mlx_load_png("./sprites/animations/player2.png");
	else if (i == 2)
		player_text = mlx_load_png("./sprites/animations/player3.png");
	else if (i == 3)
		player_text = mlx_load_png("./sprites/animations/player4.png");
	else if (i == 4)
		player_text = mlx_load_png("./sprites/animations/player5.png");
	else if (i == 5)
		player_text = mlx_load_png("./sprites/animations/player6.png");
	else
		player_text = mlx_load_png("./sprites/animations/player7.png");
	if (!player_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->player_img[i] = mlx_texture_to_image(game->mlx, player_text);
	if (!game->player_img[i])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(player_text);
	game->player_img_i = i;
}

void	player_animation(t_game *game)
{
	static int	i;
	int			k;
	int			x;
	int			y;

	if (game->attack == 1)
		attack_animation(game);
	else
	{
	x = game->player_img[i]->instances[0].x;
	y = game->player_img[i]->instances[0].y;
	mlx_delete_image(game->mlx, game->player_img[i]);
	game->player_img[i] = NULL;
	if (i == 6)
		k = 0;
	else
		k = i + 1;
	set_player_image(game, k);
	if (mlx_image_to_window(game->mlx, game->player_img[k], \
	x, y) < 0)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(&game->player_img[k]->instances[0], 3);
	i++;
	if (i == 7)
		i = 0;
	}
}

void	animation_hook(void *param)
{
	t_game			*game;
	static double	prev_time;
	double			time;

	game = param;
	time = mlx_get_time();
	if (time > prev_time + 0.15 && game->collectible_count != -3)
	{
		player_animation(game);
		prev_time = time;
	}
}