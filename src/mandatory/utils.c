/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:29:30 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:29:32 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
