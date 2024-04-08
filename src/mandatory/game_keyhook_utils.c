/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keyhook_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:28:22 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:28:24 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_wall(t_game *game, int num)
{
	int	x;
	int	y;

	x = game->player_coord[0];
	y = game->player_coord[1];
	if (num == 1 && game->map[y - 1][x].type == '1')
		return (1);
	else if (num == 2 && game->map[y + 1][x].type == '1')
		return (1);
	else if (num == 3 && game->map[y][x - 1].type == '1')
		return (1);
	else if (num == 4 && game->map[y][x + 1].type == '1')
		return (1);
	return (0);
}

int	is_close_to_wall(t_game *game, char c)
{
	int	player_x;
	int	player_y;

	player_x = game->player_coord[0];
	player_y = game->player_coord[1];
	if ((c == 'W' || c == 'S') && \
	(player_y <= 3 || player_y >= game->map_height - 5))
		return (0);
	if ((c == 'A' || c == 'D') && \
	(player_x <= 6 || player_x >= game->map_width - 7))
		return (0);
	return (1);
}
