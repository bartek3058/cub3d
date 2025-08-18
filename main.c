#include "include/cub3D.h"

int main (void)
{
    void    *mlx_connection;
    void    *mlx_window;

    mlx_connection = mlx_init();
    mlx_window = mlx_new_window(mlx_connection, 500, 500, "My window");
    mlx_pixel_put(mlx_connection, mlx_window, 250, 250, 0xFFFFFF);
    mlx_loop(mlx_connection);
}