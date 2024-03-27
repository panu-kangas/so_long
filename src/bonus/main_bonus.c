#include "so_long_bonus.h"

void	set_enemies(t_game *game)
{
	// I could have some sort of system to change this value in the beginning of game.
	// For example: player could choose to play on Easy, Hard or God mode -difficulty level.
	game->enemy_count = 2;

	game->enemy_img_i = 0;

	// randomize these! use srand() && rand(). 
	// conditions: enemy x & y cannot be +/- 2 from player. Enemy can't be in a wall.
	// Enemy can't be surrounded by walls!!
	game->enemy_coord[0][0] = 1;
	game->enemy_coord[0][1] = 1;
	game->enemy_coord[0][2] = -1;
	game->enemy_coord[0][3] = -1;
	game->enemy_coord[0][4] = 0;

	game->enemy_coord[1][0] = 1;
	game->enemy_coord[1][1] = 8;
	game->enemy_coord[1][2] = -1;
	game->enemy_coord[1][3] = -1;
	game->enemy_coord[1][4] = 1;

/*	game->enemy_coord[2][0] = 9;
	game->enemy_coord[2][1] = 9;
	game->enemy_coord[2][2] = -1;
	game->enemy_coord[2][3] = -1;
	game->enemy_coord[2][4] = 2;

	game->enemy_coord[3][0] = 12;
	game->enemy_coord[3][1] = 12;
	game->enemy_coord[3][2] = -1;
	game->enemy_coord[3][3] = -1;
	game->enemy_coord[3][4] = 3;  */
}

void	get_c_count(t_game *game)
{
	int	i;

	i = 0;
	while (game->map_file_str[i] != '\0')
	{
		if (game->map_file_str[i] == 'C')
			game->collectible_count++;
		i++;
	}
}

void	set_window_size(t_game *game)
{
	game->window_width = game->map_width * 70;
	game->window_height = game->map_height * 70;
	if (game->window_width > 1050)
	{
		game->window_width = 1050;
		game->map_is_big = 1;
	}
	if (game->window_height > 700)
	{
		game->window_height = 700;
		game->map_is_big = 1;
	}
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

void	init_game_struct(t_game *game)
{
	int	i;

	game->mlx = NULL;
	i = -1;
	while (++i < 7)
		game->player_img[i] = NULL;
	game->collectible_img[0] = NULL; // should i set all of them to NULL ??
	game->exit_img[0] = NULL;
	game->exit_img[1] = NULL;
	game->c_text = NULL;
	game->c_text2 = NULL;
	game->c_num = NULL;
	game->map = NULL;
	game->map_file_str = NULL;
	game->map_file_fd = -2;
	game->map_is_big = 0;
	game->map_height = 0;
	game->map_width = 0;
	game->window_height = 0;
	game->window_width = 0;
	game->collectible_count = 0;
	game->draw_coord[0] = 0;
	game->draw_coord[1] = 0;
	game->collectible_img_i = 0;
	game->attack = 0;
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	mlx_image_t *background_up;
	
	game = malloc(1 * sizeof(t_game));
	if (game == NULL)
		sys_error_exit(game, NULL, "Malloc failed");
	init_game_struct(game);
	check_args(game, argc, argv);
	parse_map(game);
	set_window_size(game);
	game->mlx = mlx_init(game->window_width, game->window_height + 40, \
	"so_long", false);
	if (!game->mlx)
		error_exit(game, game->mlx, mlx_strerror(mlx_errno));
	get_c_count(game);
	set_enemies(game);
	draw_map(game, 0);



// BACKGROUND IMAGE
	background_up = mlx_new_image(game->mlx, 240, 20);
	uint32_t x, y;
	y = 0;
	while (y < background_up->height)
	{
		x = 0;
		while (x < background_up->width)
		{
			mlx_put_pixel(background_up, x, y, ft_pixel(196, 107, 65, 255));
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, background_up, 0, 0);
	mlx_set_instance_depth(&background_up->instances[0], 2);
// BACKGROUND IMAGE

	mlx_loop_hook(game->mlx, &enemy_hook, game);
	mlx_loop_hook(game->mlx, &text_hook, game);
	mlx_loop_hook(game->mlx, &animation_hook, game);
	mlx_key_hook(game->mlx, &game_keyhook, game);


	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	if (game->map_file_fd >= 0)
		close(game->map_file_fd);
	ft_free_game_struct(game);
	return (0);
}
