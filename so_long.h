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
	char			type;	// 0 = floor, 1 = wall, P = Player, C = Collectible, E = exit
	int				flood_fill; // 0 = not checked, 1 = filled, -1 = not fillable
	int				dist_to_player;
	mlx_instance_t	*instance;
}			t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*player_img;
	mlx_image_t	*collectible_img; // most likely need this
	mlx_image_t	*exit_img;
	mlx_image_t	*c_text;
	mlx_image_t	*c_text2;
	mlx_image_t	*c_num;
	t_map		**map;
	char		*map_file_str;
	int			map_file_fd;
	int			map_line_count;
	int			map_line_len;
	int			collectible_count;
	int			player_coord[2];
	int			exit_coord[2];
}			t_game;

void		draw_all(t_game *game);
void		check_args(t_game *game, int argc, char **argv);
void		write_error(t_game *game, mlx_t *mlx, char *err_str);
void		write_sys_error(t_game *game, mlx_t *mlx, char *err_str);
void		parse_map(t_game *game);
void		ft_free_game_struct(t_game *game);
char		*get_map_str(t_game *game);
int			validate_map(t_game *game, char *map_file_str);
void		flood_fill(t_game *game);
void		get_dist_to_player(t_game *game);
void		text_hook(void *param);
void		find_char_in_map(t_game *game, char c, int *coordinates);



#endif