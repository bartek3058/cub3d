#include "../../include/cub3D.h"

int	close_hook(t_mygame *game)
{
	mlx_loop_end(game->mlx);
	return (1);
}

int	keys_hook(int keycode, t_mygame *game)
{
	// int	new_x_pos;
	// int	new_y_pos;

	// new_x_pos = game->p->pos[0];
	// new_y_pos = game->p->pos[1];
	// if (keycode == 119)
	// 	new_y_pos -= 1;
	// else if (keycode == 115)
	// 	new_y_pos += 1;
	// else if (keycode == 97)
	// {
	// 	new_x_pos -= 1;
	// 	so_long->p->is_facing_right = 0;
	// }
	// else if (keycode == 100)
	// {
	// 	new_x_pos += 1;
	// 	so_long->p->is_facing_right = 1;
	// }
	// else if (keycode == 65307)
	// 	mlx_loop_end(so_long->mlx);
	// player_move(so_long, new_x_pos, new_y_pos);
    if (keycode == 65307)
	 	mlx_loop_end(game->mlx);
	return (1);
}