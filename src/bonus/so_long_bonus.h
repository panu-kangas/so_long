#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "MLX42.h" // Fix this later
# include <libft.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>

typedef struct s_map
{
	char	type;
	int		flood_fill;
	int		dist_to_player;
	int		c_instance;
}			t_map;

typedef struct s_enemy
{
	int	x;
	int	y;
	int	direction;
	int	step_count;
	int	instance;
	int	is_dying;
	int	is_dead;
}			t_enemy;

typedef struct s_game // CHECK THAT ALL IS NEEDED !!
{
	mlx_t		*mlx;
	mlx_image_t	*floor_img;
	mlx_image_t	*wall_img;
	mlx_image_t	*player_img[7];
	mlx_image_t *enemy_img[7];
	mlx_image_t	*enemy_dead_img;
	mlx_image_t	*collectible_img[6];
	mlx_image_t	*exit_img[2];
	mlx_image_t	*attack_img[2];
	mlx_image_t	*c_text;
	mlx_image_t	*c_text2;
	mlx_image_t	*c_num;
	mlx_image_t	*total_moves;
	t_map		**map;
	t_enemy		*enemies;
	char		*map_file_str;
	char		left_right;
	int			map_file_fd;
	int			map_is_big;
	int			map_height;
	int			map_width;
	int			window_height;
	int			window_width;
	int			collectible_count;
	int			enemy_count;
	int			player_coord[2];
	int			exit_co[2];
	int			draw_coord[2];
	int			f_count;
	int			w_count;
	int			c_count;
	int			e_count;
	int			player_img_i;
	int			collectible_img_i;
	int			enemy_img_i;
	int			attack;
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
void		draw_map(t_game *game, int flag);
void		draw_images(t_game *game, int flag);
void		draw_floor(t_game *game, int *draw_coord);
void		draw_wall(t_game *game, int *draw_coord);
void		draw_player(t_game *game, int *draw_coord);
void		draw_collectible(t_game *game, int x, int y, int *draw_coord);
void		draw_enemy(t_game *game, int x, int y, int *draw_coord);
void		draw_exit(t_game *game, int *draw_coord);
int			is_close_to_wall(t_game *game, char c);
int			check_wall(t_game *game, int num);
void		delete_text_images(t_game *game);
void		is_game_over(t_game *game);
int			move_count_to_window(t_game *game, int move_count);

void		animation_hook(void *param);
void		attack_animation(t_game *game);
void		set_collectible_image(t_game *game, int i);

void		set_enemy_image(t_game *game, int i);
void		enemy_hook(void *param);
void		check_for_hit(t_game *game);
void		write_ending(t_game *game, char *str);

void		player_animation(t_game *game);



#endif
