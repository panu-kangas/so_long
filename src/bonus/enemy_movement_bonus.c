/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:32:45 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:32:47 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
		mlx_set_instance_depth(\
		&game->enemy_img[game->enemy_img_i]->instances[game->e_count++], 4);
	}
}

int	check_enemy_wall(t_game *game, int direction, int i)
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
	if (check_other_enemies(game, direction, i) == 1)
		return (1);
	else
		return (0);
}

void	change_enemy_coord(t_game *game, int direction, int i)
{
	if (direction == 0)
		game->enemies[i].y -= 1;
	else if (direction == 2)
		game->enemies[i].y += 1;
	else if (direction == 3)
		game->enemies[i].x -= 1;
	else if (direction == 1)
		game->enemies[i].x += 1;
	game->enemies[i].step_count--;
}

int	get_enemy_direction(t_game *game, int return_direction, int i)
{
	int	direction;
	int	counter;

	sranddev();
	direction = rand() % 4;
	counter = 0;
	while (1)
	{
		if (check_enemy_wall(game, direction, i) == 0 \
		&& direction != return_direction)
			break ;
		direction++;
		counter++;
		if (direction == 4)
			direction = 0;
		if (counter == 4)
		{
			if (check_enemy_wall(game, return_direction, i) == 0)
				direction = return_direction;
			else
				direction = -1;
			break ;
		}
	}
	return (direction);
}

void	enemy_movement(t_game *game, int i)
{
	int	direction;
	int	return_direction;
	int	step_count;

	direction = game->enemies[i].direction;
	return_direction = set_return_direction(direction);
	step_count = game->enemies[i].step_count;
	if (step_count == 0 || step_count == -1)
	{
		direction = get_enemy_direction(game, return_direction, i);
		sranddev();
		step_count = rand() % 7 + 1;
		return_direction = set_return_direction(direction);
		game->enemies[i].direction = direction;
		game->enemies[i].step_count = step_count;
	}
	change_enemy_coord(game, direction, i);
	check_for_hit(game);
	move_enemy_img(game, game->enemies[i].x, game->enemies[i].y, i);
	if (direction == -1 || check_enemy_wall(game, direction, i) == 1)
		game->enemies[i].step_count = 0;
}
