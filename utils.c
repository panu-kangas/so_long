#include "so_long.h"

void	find_char_in_map(t_game *game, char c, int *coordinates) // MIGHT BE USELESS!!
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_line_count)
	{
		x = 0;
		while (x < game->map_line_len)
		{
			if (game->map[y][x].type == c)
				break ;
			x++;
		}
		if (x != game->map_line_len)
			break ;
		y++;
	}
	coordinates[0] = x;
	coordinates[1] = y;
}

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
			break;
		map_str = get_str(map_str, buf, bytes);
		if (map_str == NULL)
			write_sys_error(game, NULL, "Malloc failed");
	}
	if (bytes == -1)
		write_sys_error(game, NULL, "Read failed");
	return (map_str);
}
