/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:35:20 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:35:21 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*get_str(char *map_str, char *buf, int bytes)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = malloc((ft_strlen(map_str) + bytes + 1) * sizeof(char));
	if (temp == NULL)
	{
		free(map_str);
		return (NULL);
	}
	while (map_str != NULL && map_str[j] != '\0')
		temp[i++] = map_str[j++];
	free(map_str);
	j = 0;
	while (j < bytes)
		temp[i++] = buf[j++];
	temp[i] = '\0';
	map_str = ft_strdup(temp);
	free(temp);
	return (map_str);
}

char	*get_map_str(t_game *game)
{
	char	buf[100];
	char	*map_str;
	int		bytes;

	map_str = NULL;
	while (1)
	{
		bytes = read(game->map_file_fd, buf, 100);
		if (bytes == -1 || bytes == 0)
			break ;
		map_str = get_str(map_str, buf, bytes);
		if (map_str == NULL)
			sys_error_exit(game, NULL, "Malloc failed");
	}
	if (bytes == -1)
		sys_error_exit(game, NULL, "Read failed");
	return (map_str);
}

void	total_moves_to_window(t_game *game)
{
	char	*num;

	if (mlx_put_string(game->mlx, "Total moves count: ", \
	0, 0) == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	num = ft_itoa(0);
	if (num == NULL)
		sys_error_exit(game, game->mlx, "Malloc failed");
	game->total_moves = mlx_put_string(game->mlx, num, \
	190, 0);
	free(num);
	num = NULL;
	if (!game->total_moves)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
}

int	start_text_to_window(t_game *game, int c_count)
{
	char	*num;

	game->c_text = mlx_put_string(game->mlx, "Get the diamonds!", \
	0, game->mlx->height - 40);
	if (game->c_text == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	game->c_text2 = mlx_put_string(game->mlx, "Diamond count: ", \
	0, game->mlx->height - 20);
	if (game->c_text2 == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	num = ft_itoa(c_count);
	if (num == NULL)
		sys_error_exit(game, game->mlx, "Malloc failed");
	game->c_num = mlx_put_string(game->mlx, num, \
	150, game->mlx->height - 20);
	free(num);
	num = NULL;
	if (game->c_num == NULL)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	total_moves_to_window(game);
	return (1);
}

void	set_enemy_struct(t_game *game, int i, int x, int y)
{
	game->enemies[i].x = x;
	game->enemies[i].y = y;
	game->enemies[i].direction = -1;
	game->enemies[i].step_count = -1;
	game->enemies[i].is_dying = 0;
	game->enemies[i].is_dead = 0;
}
