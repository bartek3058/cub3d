#include "include/cub3D.h"

int main (int argc, char **argv)
{
    // t_mygame game;
    void    *mlx_connection;
    void    *mlx_window;

    check_map_name(argc, argv);
    load_map(argv[1]);
    // configuration_map_checker(game, argv);
    mlx_connection = mlx_init();
    mlx_window = mlx_new_window(mlx_connection, 500, 500, "My window");
    mlx_pixel_put(mlx_connection, mlx_window, 250, 250, 0xFFFFFF);
    mlx_loop(mlx_connection);
}