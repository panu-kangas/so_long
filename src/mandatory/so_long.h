#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_map
{
	char	type;
	int		flood_fill;
	int		dist_to_player;
	int		c_instance;
}			t_map;

typedef struct s_game // CHECK THAT ALL IS NEEDED !!
{
	mlx_t		*mlx;
	mlx_image_t	*floor_img;
	mlx_image_t	*wall_img;
	mlx_image_t	*player_img;
	mlx_image_t	*collectible_img;
	mlx_image_t	*exit_img[2];
	mlx_image_t	*c_text;
	mlx_image_t	*c_text2;
	mlx_image_t	*c_num;
	t_map		**map;
	char		*map_file_str;
	int			map_file_fd;
	int			map_is_big;
	int			map_height;
	int			map_width;
	int			window_height;
	int			window_width;
	int			collectible_count;
	int			player_coord[2];
	int			exit_co[2];
	int			draw_coord[2];
	int			f_count;
	int			w_count;
	int			c_count;
}			t_game;

void		check_args(t_game *game, int argc, char **argv);
void		error_exit(t_game *game, mlx_t *mlx, const char *err_str);
void		sys_error_exit(t_game *game, mlx_t *mlx, const char *err_str);
void		parse_map(t_game *game);
void		ft_free_game_struct(t_game *game);
char		*get_map_str(t_game *game);
int			validate_map(t_game *game, char *map_file_str);
void		flood_fill(t_game *game);
void		get_dist_to_player(t_game *game);
void		text_hook(void *param);
void		find_char_in_map(t_game *game, char c, int *coordinates);
void		game_keyhook(mlx_key_data_t keydata, void *param);
int			get_x_start(t_game *game);
int			get_y_start(t_game *game);
void		draw_map(t_game *game);
void		draw_images(t_game *game);
void		draw_floor(t_game *game, int *draw_coord);
void		draw_wall(t_game *game, int *draw_coord);
void		draw_player(t_game *game, int *draw_coord);
void		draw_collectible(t_game *game, int x, int y, int *draw_coord);
void		draw_exit(t_game *game, int *draw_coord);
int			is_close_to_wall(t_game *game, char c);
int			check_wall(t_game *game, int num);
void		delete_text_images(t_game *game);
void		is_game_over(t_game *game);
int			move_count_to_window(t_game *game, int move_count);

#endif
