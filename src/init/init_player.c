#include "../../include/cub3d.h"

void init_player_from_map(t_mygame *game)
{
    for (int y = 0; y < game->map.height; y++)
    {
        for (int x = 0; x < game->map.width; x++)
        {
            char cell = game->map.grid[y][x];
            if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
            {
                game->player.x = x;
                game->player.y = y;
                if (cell == 'N') { game->player.dir_x = 0; game->player.dir_y = -1; }
                if (cell == 'S') { game->player.dir_x = 0; game->player.dir_y = 1; }
                if (cell == 'E') { game->player.dir_x = 1; game->player.dir_y = 0; }
                if (cell == 'W') { game->player.dir_x = -1; game->player.dir_y = 0; }
                game->map.grid[y][x] = '0'; // Remove player marker from map
                return;
            }
        }
    }
}