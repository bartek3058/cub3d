#include "../../include/cub3d.h"

// void flood_check(t_mygame *game, int y, int x)
// {
//     char **grid;

//     grid = game->map.grid;
//     if (y < 0 || y >= game->map.height || x < 0 || x >= (int)ft_strlen(grid[y]))
//     {
//         free_map_grid(game);
//         free_myconfig(&game->config);
//         exit_error("Error: map not closed (edge)");
//     }
//     if (grid[y][x] == ' ' )
//     {
//         free_map_grid(game);
//         free_myconfig(&game->config);
//         exit_error("Error: map not closed (space hole)");
//     }
//     if (grid[y][x] == '1' || grid[y][x] == 'V') 
//         return;
//     grid[y][x] = 'V';
//     flood_check(game, y - 1, x);
//     flood_check(game, y + 1, x);
//     flood_check(game, y, x - 1);
//     flood_check(game, y, x + 1);
// }

