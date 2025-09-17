#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>


// structures

typedef struct s_mymap
{
    char        **grid;     // tablica znaków mapy
    int         width;      // szerokość mapy
    int         height;     // wysokość mapy
}   t_mymap;

typedef struct s_myplayer
{
    double      x;          // pozycja X (float/double dla płynności)
    double      y;          // pozycja Y
    double      dir_x;      // wektor kierunku X
    double      dir_y;      // wektor kierunku Y
    double      plane_x;    // wektor kamery X (FOV)
    double      plane_y;    // wektor kamery Y
}   t_myplayer;

typedef struct s_myimg
{
    void    *img;       // wskaźnik MLX na obraz
    char    *addr;      // adres danych obrazu
    int     bpp;        // bity na piksel
    int     line_len;   // długość linii w bajtach
    int     endian;     // endian
}   t_myimg;

typedef struct s_mytextures
{
    t_myimg       north;
    t_myimg       south;
    t_myimg       west;
    t_myimg       east;
}   t_mytextures;

typedef struct s_myconfig
{
    char    *tex_no;    // ścieżka do NO
    char    *tex_so;    // ścieżka do SO
    char    *tex_we;    // ścieżka do WE
    char    *tex_ea;    // ścieżka do EA
    int     floor_color; // kolor podłogi (RGB jako int)
    int     ceil_color;  // kolor sufitu
}   t_myconfig;

typedef struct s_myray
{
    double  camera_x;
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
}   t_myray;

typedef struct s_mygame
{
    void        *mlx;       // wskaźnik MLX
    void        *win;       // okno MLX
    t_mymap       map;        // mapa gry
    t_myplayer    player;     // gracz
    t_mytextures  textures;   // tekstury
    t_myimg       img;        // bufor obrazu
    t_myconfig    config;     // kolory, ścieżki tekstur
}   t_mygame;


// Functions

// map
void    check_map_name(int argc, char **argv);
void    check_map_size(char **argv);
char    **load_map(char *filename);

//free
void	free_split(char **arr);

//parser
void	parser(char **lines, t_mygame *game);
int parse_map(t_mygame *game);
void set_player_direction(t_myplayer *player, char dir);
int parse_config(char **lines, t_mygame *game);
int is_blank(const char *s);


//init
void    init_myconfig(t_mygame *game);
void	init_map(t_mygame *game, char **lines, int a);

//init
int    init_window(t_mygame *game);

//hooks
int	close_hook(t_mygame *game);
int	keys_hook(int keycode, t_mygame *game);

//cleanup
void    cleanup_display(t_mygame *game);
void    cleanup_all(t_mygame *game);

//utils
int	ft_strcmp(const char *s1, const char *s2);

//2d_map
void   draw_square(t_myimg *img, int x, int y, int color);

#endif