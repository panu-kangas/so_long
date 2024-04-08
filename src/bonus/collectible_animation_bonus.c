/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_animation_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:31:33 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:31:35 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	collect_to_window1(t_game *game, int *draw_co, int instance, int i)
{
	if (mlx_image_to_window(game->mlx, game->collectible_img[i + 1], \
	draw_co[0] + 24, draw_co[1] + 27) < 0)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(\
	&game->collectible_img[i + 1]->instances[instance], 2);
}

void	collect_to_window2(t_game *game, int *draw_co, int instance, int i)
{
	if (mlx_image_to_window(game->mlx, game->collectible_img[i - 1], \
	draw_co[0] + 24, draw_co[1] + 27) < 0)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_set_instance_depth(\
	&game->collectible_img[i - 1]->instances[instance], 2);
}

void	collectible_loop(t_game *game, int flag, int i, int instance)
{
	int			draw_co[2];
	int			x;
	int			y;

	y = get_y_start(game);
	draw_co[1] = 0;
	while (draw_co[1] < game->window_height)
	{
		x = get_x_start(game);
		draw_co[0] = 0;
		while (draw_co[0] < game->window_width)
		{
			if (game->map[y][x++].type == 'C')
			{
				if (flag == 0)
					collect_to_window1(game, draw_co, instance, i);
				if (flag == -1)
					collect_to_window2(game, draw_co, instance, i);
				game->map[y][x - 1].c_instance = instance++;
			}
			draw_co[0] += 70;
		}
		y++;
		draw_co[1] += 70;
	}
}

void	set_collectible_image(t_game *game, int i)
{
	mlx_texture_t	*collect_text;

	if (i == 0)
		collect_text = mlx_load_png("./sprites/animations/collect1.png");
	else if (i == 1)
		collect_text = mlx_load_png("./sprites/animations/collect2.png");
	else if (i == 2)
		collect_text = mlx_load_png("./sprites/animations/collect3.png");
	else if (i == 3)
		collect_text = mlx_load_png("./sprites/animations/collect4.png");
	else if (i == 4)
		collect_text = mlx_load_png("./sprites/animations/collect5.png");
	else
		collect_text = mlx_load_png("./sprites/animations/collect6.png");
	if (!collect_text)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->collectible_img[i] = mlx_texture_to_image(game->mlx, collect_text);
	if (!game->collectible_img[i])
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	mlx_delete_texture(collect_text);
}

void	collectible_animation(t_game *game)
{
	static int	i;
	static int	flag;

	mlx_delete_image(game->mlx, game->collectible_img[i]);
	if (flag == 0)
		set_collectible_image(game, i + 1);
	else if (flag == -1)
		set_collectible_image(game, i - 1);
	collectible_loop(game, flag, i, 0);
	if (flag == 0)
	{
		i++;
		if (i == 5)
			flag = -1;
	}
	else if (flag == -1)
	{
		i--;
		if (i == 0)
			flag = 0;
	}
	game->collectible_img_i = i;
}
