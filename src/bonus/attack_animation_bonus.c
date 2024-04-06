#include "so_long_bonus.h"

int	execute_attack(t_game *game, int x, int y, int flag)
{
	if (flag == 0)
	{
		game->player_img[game->player_img_i]->enabled = 0;
		if (mlx_image_to_window(game->mlx, game->attack_img[0], \
		x, y) < 0)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		mlx_set_instance_depth(&game->attack_img[0]->instances[0], 3);
		return (1);
	}
	else if (flag == 1)
	{
		mlx_delete_image(game->mlx, game->attack_img[0]);
		if (mlx_image_to_window(game->mlx, game->attack_img[1], \
		x, y) < 0)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		mlx_set_instance_depth(&game->attack_img[1]->instances[0], 3);
		return (2);
	}
	else
	{
		mlx_delete_image(game->mlx, game->attack_img[1]);
		game->player_img[game->player_img_i]->enabled = 1;
		game->attack = 0;
		return (0);
	}
}

void	set_attack_img(t_game *game, mlx_texture_t **attack_text)
{
	if (game->left_right == 'R')
		attack_text[0] = mlx_load_png("./sprites/animations/attack1.png");
	else
		attack_text[0] = mlx_load_png("./sprites/animations/attack1_mirr.png");
	if (!attack_text[0])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	if (game->left_right == 'R')
		attack_text[1] = mlx_load_png("./sprites/animations/attack2.png");
	else
		attack_text[1] = mlx_load_png("./sprites/animations/attack2_mirr.png");
	if (!attack_text[1])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
}

void	attack_animation(t_game *game)
{
	mlx_texture_t	*attack_text[2];
	int				x;
	int				y;
	static int		flag;

	x = game->player_img[game->player_img_i]->instances[0].x;
	y = game->player_img[game->player_img_i]->instances[0].y;
	set_attack_img(game, attack_text);
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
	if (game->left_right == 'L')
		x -= 30;
	flag = execute_attack(game, x, y, flag);
}
