#include "../../include/cub3d.h"

int	close_hook(t_mygame *game)
{
	mlx_loop_end(game->mlx);
	return (1);
}

int	keys_hook(int keycode, t_mygame *game)
{
	int	new_x_pos;
	int	new_y_pos;

	new_x_pos = game->player.x;
	new_y_pos = game->player.y;
	if (keycode == 119)
		new_y_pos -= 1;
	else if (keycode == 115)
		new_y_pos += 1;
	else if (keycode == 97)
		new_x_pos -= 1;
	else if (keycode == 100)
		new_x_pos += 1;
    else if (keycode == 65307)
	 	mlx_loop_end(game->mlx);
	move_player(game, new_x_pos, new_y_pos);
	return (1);
}
