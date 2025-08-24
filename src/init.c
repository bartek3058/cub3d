#include "../include/cub3D.h"

int    init_window(t_mygame *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);
    game->win = mlx_new_window(game->mlx, 500, 500, "My window");
    if (!game->win)
        return (0);
    return (1);
}