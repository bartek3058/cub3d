/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:34:45 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/17 10:41:35 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

// structures

typedef struct s_mymap
{
	char	**grid;// tablica znaków mapy
	int		width;// szerokość mapy
	int		height;// wysokość mapy
	int		tile_size;// rozmiar kafelka
}	t_mymap;

typedef struct s_myplayer
{
	double	x;			// pozycja X (float/double dla płynności)
	double	y;			// pozycja Y
	double	dir_x;		// wektor kierunku X
	double	dir_y;		// wektor kierunku Y
	double	mv_dir_x; // wektor ruchu X
	double	mv_dir_y; // wektor ruchu Y
	double	angle;		// kąt patrzenia (w radianach)
	double	plane_x;	// wektor kamery X (FOV)
	double	plane_y;	// wektor kamery Y
	double	mv_spd;	// prędkość ruchu
	double	rot_spd;	// prędkość rotacji
	int		player_size;		// rozmiar gracza (w pikselach)
}	t_myplayer;

typedef struct s_myimg
{
	void	*img;		// wskaźnik MLX na obraz
	char	*addr;		// adres danych obrazu
	int		bpp;		// bity na piksel
	int		line_len;	// długość linii w bajtach
	int		endian;		// endian
	int		width;		// szerokość obrazu
	int		height;		// wysokość obrazu
}	t_myimg;

typedef struct s_mytextures
{
	t_myimg	north;
	t_myimg	south;
	t_myimg	west;
	t_myimg	east;
}	t_mytextures;

typedef struct s_myconfig
{
	char	*tex_no;	// ścieżka do NO
	char	*tex_so;	// ścieżka do SO
	char	*tex_we;	// ścieżka do WE
	char	*tex_ea;	// ścieżka do EA
	int		floor_color;// kolor podłogi (RGB jako int)
	int		ceil_color;	// kolor sufitu
}	t_myconfig;

typedef struct s_myray
{
	double	cam_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_myray;

typedef struct s_mygame
{
	void			*mlx;		// wskaźnik MLX
	void			*win;		// okno MLX
	t_mymap			map;		// mapa gry
	t_myplayer		player;		// gracz
	t_mytextures	textures;	// tekstury
	t_myimg			img;		// bufor obrazu
	t_myconfig		config;		// kolory, ścieżki tekstur
	t_myray			ray;		// dane raycastera
	int				key_w;		// W
	int				key_s;		// S
	int				key_a;		// A
	int				key_d;		// D
	int				key_left_arrow;
	int				key_right_arrow;
	int				key_esc;	// ESC
	int				scr_width;	// szerokość okna
	int				scr_height;	// wysokość okna
	int				prev_mouse_x; // poprzednia pozycja myszy X
	int				prev_mouse_y; // poprzednia pozycja myszy Y
}	t_mygame;

// some structures for help (norminette)

typedef struct s_draw_player_vars
{
	int	x;
	int	y;
	int	px;
	int	py;
	int	i;
	int	j;
}	t_draw_player_vars;

typedef struct s_parse_ctx
{
	t_mygame	*game;
	char		**lines;
}	t_parse_ctx;

typedef struct s_color_ctx
{
	char		**lines;
	char		**rgb;
	char		**parts;
	t_mygame	*game;
}	t_color_ctx;

typedef struct s_tex_ctx
{
	t_parse_ctx	*ctx;
	char		**parts;
}	t_tex_ctx;

// Functions
//main
int		game_loop(t_mygame *game);

// map
void	check_map_name(int argc, char **argv);
void	check_map_size(char **argv);
char	**load_map(t_mygame *game, char *filename);

//background
void	draw_background(t_mygame *game);

//free
void	free_split(char **arr);
void	free_myconfig(t_myconfig *cfg);
void	free_map_grid(t_mygame *game);

//parser
void	parser(char **lines, t_mygame *game);
int		parse_map(char **lines, t_mygame *game);
void	set_player_direction(t_myplayer *player, char dir);
int		parse_config(char **lines, t_mygame *game);
void	draw_background(t_mygame *game);
int		parse_color(char *str, char **lines, char **parts, t_mygame *game);
void	check_trailing_lines(char **lines, int map_end_index, t_mygame *game);
int		starts_with_token(const char *s, const char *tok);
void	validate_map_closed(char **lines, t_mygame *game);
void	map_parse_error(t_parse_ctx *ctx, char *msg);
void	flood_check(char **lines, t_mygame *game, int y, int x);
int		is_config_line(char *line);
void	save_config_line(t_mygame *game, char *line, char **lines);
int		is_player_char(char c);

//init
void	init_map(t_mygame *game, char **lines, int a);
int		init_image(t_mygame *game, int width, int height);

//init
int		init_window(t_mygame *game);
void	init_game(t_mygame *game);

//init player
void	init_player(t_mygame *game);

//init_t_game
int		load_texture(t_mygame *game, t_myimg *img, char *path);
int		load_textures(t_mygame *game);

//hooks
int		close_hook(t_mygame *game);
int		key_press(int keycode, t_mygame *game);
int		key_release(int keycode, t_mygame *game);
int		mouse_move(int x, int y, t_mygame *game);
void	update_camera_vectors(t_myplayer *player, double angle);

//cleanup
void	cleanup_display(t_mygame *game);
void	cleanup_all(t_mygame *game);

//utils
void	check_config(char **lines, t_mygame *game);
int		ft_strcmp(const char *s1, const char *s2);
int		is_blank(const char *s);
void	check_color(t_color_ctx *ctx, int r, int g, int b);
void	save_texture(t_parse_ctx *ctx, char *key, char *value, char **parts);
void	save_color(t_parse_ctx *ctx, char *key, char *value, char **parts);
void	exit_error(const char *msg);
char	*ft_strtrim(char const *s1, char const *set);
int		parse_single_color_component(t_color_ctx *ctx, char *component);

//2d_map
void	draw_square(t_mygame *game, int x, int y, int color);
void	draw_2d_map(t_mygame *game);
void	draw_player(t_mygame *game);
void	draw_pixel_to_buffer(t_myimg *img, int x, int y, int color);
void	draw_crosshair(t_mygame *game);
void	draw_nose(t_mygame *game, t_myplayer *player, int px, int py);
void	draw_mv_dir(t_mygame *game, t_myplayer *player, int px, int py);

//player
void	move_player(t_mygame *game, double new_x_pos, double new_y_pos);
void	rotate_player(t_mygame *game);
void	rotate_camera(t_mygame *game, double angle);
void	update_player_controls(t_mygame *game);

//raycaster
void	raycaster(t_myray *ray, t_mygame *game);
int		darker_color(int *color, double factor);

//textures
void	draw_textured_column(t_myray *ray, t_mygame *game, int x);
#endif
