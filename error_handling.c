#include "so_long.h"

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

void	error_exit(t_game *game, mlx_t *mlx, char *err_str)
{
	if (err_str != NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(err_str, 2);
	}
	if (game->map_file_fd >= 0)
		close(game->map_file_fd);
	if (mlx != NULL)
		mlx_terminate(mlx);
	ft_free_game_struct(game);
	exit(1);
}

void	sys_error_exit(t_game *game, mlx_t *mlx, char *err_str)
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

void	check_args(t_game *game, int argc, char **argv)
{
	char	*temp;

	if (argc != 2)
		error_exit(game, NULL, \
		"Invalid number of arguments! Insert one map-file.");
	temp = ft_strrchr(argv[1], '.');
	if (temp == NULL)
		error_exit(game, NULL, \
		"Invalid file type! Only files with '.ber' extension are accepted");
	if (ft_strncmp(temp, ".ber", 5) != 0)
		error_exit(game, NULL, \
		"Invalid file type! Only files with '.ber' extension are accepted");
	game->map_file_fd = open(argv[1], O_RDONLY);
	if (game->map_file_fd < 0)
		sys_error_exit(game, NULL, "Open failed");
}
