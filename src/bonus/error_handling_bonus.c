#include "so_long_bonus.h"

void	ft_free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map != NULL)
	{
		while (i < game->map_height)
			free(game->map[i++]);
	}
	free(game->map);
}

void	ft_free_game_struct(t_game *game)
{
	if (game != NULL)
	{
		ft_free_map(game);
		free(game->map_file_str);
	}
	free(game);
}

void	error_exit(t_game *game, mlx_t *mlx, const char *err_str)
{
	if (err_str != NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd((char *)err_str, 2);
	}
	if (game->map_file_fd >= 0)
		close(game->map_file_fd);
	if (mlx != NULL)
		mlx_terminate(mlx);
	ft_free_game_struct(game);
	exit(1);
}

void	sys_error_exit(t_game *game, mlx_t *mlx, const char *err_str)
{
	ft_putendl_fd("Error", 2);
	perror(err_str);
	if (game->map_file_fd >= 0)
		close(game->map_file_fd);
	if (mlx != NULL)
		mlx_terminate(mlx);
	ft_free_game_struct(game);
	exit(1);
}
