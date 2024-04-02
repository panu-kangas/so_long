#include "so_long_bonus.h"

int	check_start_coords(t_game *game, int i, int x, int y)
{
	if (game->enemy_count == 1)
		return (0);
	while (--i > -1)
	{
		if (x == game->enemies[i].x && y == game->enemies[i].y)
			return (1);
	}
	if (x >= game->player_coord[0] - 2 && x <= game->player_coord[0] + 2 && \
	y >= game->player_coord[1] - 2 && y <= game->player_coord[1] + 2)
		return (1);
	else
		return (0);
}

int	get_rand_coord(t_game *game, char xy)
{
	int			coord;
	int			max;

	if (xy == 'x')
		max = game->map_width - 1;
	else
		max = game->map_height - 1;

	coord = rand() % max;

	return (coord);
}

void	set_enemies(t_game *game)
{
	int	i;
	int	x;
	int	y;

	// I could have some sort of system to change this value in the beginning of game.
	// For example: player could choose to play on Easy, Hard or God mode -difficulty level.

	game->enemy_count = (game->f_count + game->collectible_count) / 10;
	if (game->enemy_count == 0)
		game->enemy_count++;
	game->enemy_img_i = 0;

	game->enemies = malloc(game->enemy_count * sizeof(t_enemy));
	if (game->enemies == NULL)
		sys_error_exit(game, NULL, "Malloc failed");

	i = 0;
	while (i < game->enemy_count)
	{
		x = 0;
		y = 0;
		while (game->map[y][x].type == '1' || game->map[y][x].type == 'P' || check_start_coords(game, i, x, y) == 1)
		{
			x = get_rand_coord(game, 'x');
			y = get_rand_coord(game, 'y');
			// Enemy can't be surrounded by walls!! --> does this matter...?
		}
		game->enemies[i].x = x;
		game->enemies[i].y = y;
		game->enemies[i].direction = -1;
		game->enemies[i].step_count = -1;
		game->enemies[i].is_dying = 0;
		game->enemies[i].is_dead = 0;
		i++;
	}


}

void	get_c_f_count(t_game *game)
{
	int	i;

	i = 0;
	while (game->map_file_str[i] != '\0')
	{
		if (game->map_file_str[i] == 'C')
			game->collectible_count++;
		else if (game->map_file_str[i] == '0')
			game->f_count++;
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
	game->left_right = 'R';
	game->map_file_fd = -2;
	game->map_is_big = 0;
	game->map_height = 0;
	game->map_width = 0;
	game->window_height = 0;
	game->window_width = 0;
	game->collectible_count = 0;
	game->f_count = 0;
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
	get_c_f_count(game);
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
