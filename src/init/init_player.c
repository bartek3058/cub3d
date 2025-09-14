#include "../../include/cub3d.h"

void init_player_from_map(t_mygame *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			char cell = game->map.grid[y][x];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			{
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				if (cell == 'N')
				{
					game->player.dir_x = 0;
					game->player.dir_y = -1;
				}
				if (cell == 'S')
				{
					game->player.dir_x = 0;
					game->player.dir_y = 1;
				}
				if (cell == 'E')
				{
					game->player.dir_x = 1;
					game->player.dir_y = 0;
				}
				if (cell == 'W')
				{
					game->player.dir_x = -1;
					game->player.dir_y = 0;
				}
				game->map.grid[y][x] = '0';	   // Remove player marker from map
				game->player.MOVE_SPEED = 0.001; // Set a default move speed
				return;
			}
			x++;
		}
		y++;
	}
}
