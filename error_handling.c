#include "so_long.h"

void	ft_free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map != NULL)
	{
		while (i < game->map_line_count)
			free(game->map[i++]);
	}
	free(game->map);
}

void	ft_free_game_struct(t_game *game)
{
	if (game != NULL)
		ft_free_map(game);
	
	free(game->map_file_str);

	// How to free mlx_image_t?? I mean the main char image

	free(game);
}

void	write_error(t_game *game, mlx_t *mlx, char *err_str) // Change name to error_exit !!
{
	if (err_str != NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(err_str, 2);
	}

	// close map_file_fd
	// free all allocated
	// free textures


	ft_free_game_struct(game);

	if (mlx != NULL)
		mlx_terminate(mlx);


	exit (1);
}

void	write_sys_error(t_game *game, mlx_t *mlx, char *err_str) // Change name to sys_error_exit !!
{
	ft_putendl_fd("Error", 2);
	perror(err_str);

	// close map_file_fd
	// free all allocated
	// terminate mlx

	ft_free_game_struct(game);

	if (mlx != NULL)
		mlx_terminate(mlx); // Double check this, probably not right


	exit (1);
}

void	check_args(t_game *game, int argc, char **argv)
{
	char	*temp;

	if (argc != 2)
		write_error(game, NULL, "Invalid number of arguments! Insert one map-file.");

	temp = ft_strrchr(argv[1], '.');
	if (temp == NULL)
		write_error(game, NULL, "Invalid file type! Only files with '.ber' extension are accepted");
	if (ft_strncmp(temp, ".ber", 5) != 0)
		write_error(game, NULL, "Invalid file type! Only files with '.ber' extension are accepted");

	game->map_file_fd = open(argv[1], O_RDONLY);
	if (game->map_file_fd < 0)
		write_sys_error(game, NULL, "Open failed"); // NOT TESTED

	
}