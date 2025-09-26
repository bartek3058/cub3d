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
	char	**grid;   // tablica znaków mapy
	int		width;	   // szerokość mapy
	int		height;	   // wysokość mapy
	int		tile_size; // rozmiar kafelka
}	t_mymap;

typedef struct s_myplayer
{
	double	x;			// pozycja X (float/double dla płynności)
	double	y;			// pozycja Y
	double	dir_x;		// wektor kierunku X
	double	dir_y;		// wektor kierunku Y
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
}	t_mygame;

// Functions
//main
int		game_loop(t_mygame *game);

// map
void	check_map_name(int argc, char **argv);
void	check_map_size(char **argv);
char	**load_map(char *filename);

//background
void draw_background(t_mygame *game);

//free
void	free_split(char **arr);

//parser
void	parser(char **lines, t_mygame *game);
int		parse_map(t_mygame *game);
void	set_player_direction(t_myplayer *player, char dir);
int		parse_config(char **lines, t_mygame *game);
void    draw_background(t_mygame *game);

//init
void	init_myconfig(t_mygame *game);
void	init_map(t_mygame *game, char **lines, int a);
int init_image(t_mygame *game, int width, int height);

//init
int		init_window(t_mygame *game);
void	init_game(t_mygame *game);

//init player
void	init_player(t_mygame *game);

//hooks
int		close_hook(t_mygame *game);
int		key_press(int keycode, t_mygame *game);
int		key_release(int keycode, t_mygame *game);

//cleanup
void	cleanup_display(t_mygame *game);
void	cleanup_all(t_mygame *game);

//utils
int		ft_strcmp(const char *s1, const char *s2);
int		is_blank(const char *s);

//2d_map
void	draw_square(t_myimg *img, int x, int y, int color, int size);
void	draw_2d_map(t_mygame *game);
void	draw_player(t_mygame *game);
void	draw_pixel_to_buffer(t_myimg *img, int x, int y, int color);

//player
void	move_player(t_mygame *game, double new_x_pos, double new_y_pos);
void	rotate_player(t_mygame *game, double angle);
void	update_player_controls(t_mygame *game);

//raycaster
void	raycaster(t_myray *ray, t_mygame *game);
int		darker_color(int *color, double factor);
#endif
