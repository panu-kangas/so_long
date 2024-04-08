/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkangas <pkangas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:35:27 by pkangas           #+#    #+#             */
/*   Updated: 2024/04/08 12:35:28 by pkangas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_surround(t_game *game, char *str, int line_count, int line_len)
{
	int	i;
	int	counter;

	i = -1;
	while (str[++i] != '\n')
	{
		if (str[i] != '1')
			error_exit(game, NULL, "Map is not surrounded by walls");
	}
	counter = 2;
	while (counter != line_count)
	{
		if (str[++i] != '1')
			error_exit(game, NULL, "Map is not surrounded by walls");
		while (str[i + 1] != '\n')
			i++;
		if (str[i++] != '1')
			error_exit(game, NULL, "Map is not surrounded by walls");
		counter++;
	}
	while (--line_len >= 0)
	{
		if (str[++i] != '1')
			error_exit(game, NULL, "Map is not surrounded by walls");
	}
}

void	check_counts(t_game *game, int c_count, int p_count, int e_count)
{
	if (p_count == 0)
		error_exit(game, NULL, "Map needs to have one Player ('P')");
	if (e_count == 0)
		error_exit(game, NULL, "Map needs to have one Exit ('E')");
	if (c_count == 0)
		error_exit(game, NULL, "Map needs at least one Collectible ('C')");
	if (p_count > 1)
		error_exit(game, NULL, "Map has more than one Player ('P')");
	if (e_count > 1)
		error_exit(game, NULL, "Map has more than one Exit ('E')");
}

void	check_characters(t_game *game, char *str)
{
	int	i;
	int	c_count;
	int	p_count;
	int	e_count;

	i = 0;
	c_count = 0;
	p_count = 0;
	e_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'C' && \
		str[i] != 'P' && str[i] != 'E' && str[i] != '\n')
			error_exit(game, NULL, "Invalid char in map; use only '01CPE'");
		if (str[i] == 'C')
			c_count++;
		if (str[i] == 'P')
			p_count++;
		if (str[i] == 'E')
			e_count++;
		i++;
	}
	check_counts(game, c_count, p_count, e_count);
}

int	is_rectangular(t_game *game, char *str, int line_count)
{
	int	i;
	int	i_prev;
	int	len;

	i = -1;
	len = 0;
	while (str[++i] != '\n')
		len++;
	line_count++;
	while (str[i] != '\0')
	{
		i_prev = i;
		i++;
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		if (i - i_prev - 1 != len)
			error_exit(game, NULL, "Map is not rectangular");
		line_count++;
		if (str[i] == '\n' && str[i + 1] == '\0')
			break ;
	}
	if (line_count == 1 || line_count == 2)
		error_exit(game, NULL, "Map too small; at least three lines needed");
	return (line_count);
}

int	validate_map(t_game *game, char *map_file_str)
{
	int	line_count;
	int	i;

	if (ft_strchr(map_file_str, '\n') == NULL)
		error_exit(game, NULL, "Map too small; at least three lines needed");
	line_count = is_rectangular(game, map_file_str, 0);
	i = 0;
	while (map_file_str[i] != '\n')
		i++;
	if (i < 3)
		error_exit(game, NULL, "Map too small; at least three columns needed");
	check_characters(game, map_file_str);
	check_surround(game, map_file_str, line_count, i);
	return (line_count);
}
