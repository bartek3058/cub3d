#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>


// structures

typedef struct s_game
{
    void        *mlx;       // wskaźnik MLX
    void        *win;       // okno MLX
    t_map       map;        // mapa gry
    t_player    player;     // gracz
    t_textures  textures;   // tekstury
    t_img       img;        // bufor obrazu
    t_config    config;     // kolory, ścieżki tekstur
}   t_game;

typedef struct s_map
{
    char        **grid;     // tablica znaków mapy
    int         width;      // szerokość mapy
    int         height;     // wysokość mapy
}   t_map;

typedef struct s_player
{
    double      x;          // pozycja X (float/double dla płynności)
    double      y;          // pozycja Y
    double      dir_x;      // wektor kierunku X
    double      dir_y;      // wektor kierunku Y
    double      plane_x;    // wektor kamery X (FOV)
    double      plane_y;    // wektor kamery Y
}   t_player;

typedef struct s_textures
{
    t_img       north;
    t_img       south;
    t_img       west;
    t_img       east;
}   t_textures;

typedef struct s_img
{
    void    *img;       // wskaźnik MLX na obraz
    char    *addr;      // adres danych obrazu
    int     bpp;        // bity na piksel
    int     line_len;   // długość linii w bajtach
    int     endian;     // endian
}   t_img;

typedef struct s_config
{
    char    *tex_no;    // ścieżka do NO
    char    *tex_so;    // ścieżka do SO
    char    *tex_we;    // ścieżka do WE
    char    *tex_ea;    // ścieżka do EA
    int     floor_color; // kolor podłogi (RGB jako int)
    int     ceil_color;  // kolor sufitu
}   t_config;

typedef struct s_ray
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
}   t_ray;


// Functions

// map
void    check_map_name(int argc, char **argv);
void    check_map_name(int argc, char **argv);
void    window_size(t_game *game, char **argv);


#endif