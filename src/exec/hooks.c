#include "../../include/cub3d.h"

#define MOVE_SPEED 0.1

int	close_hook(void *param)
{
    t_mygame *game = (t_mygame *)param;
    mlx_loop_end(game->mlx);
	return (1);
}

int key_press(int keycode,  void *param)
{
    t_mygame *game = (t_mygame *)param;
    if (keycode == 119) game->key_w = 1;
    if (keycode == 115) game->key_s = 1;
    if (keycode == 97)  game->key_a = 1;
    if (keycode == 100) game->key_d = 1;
    if (keycode == 65307) mlx_loop_end(game->mlx); // ESC key

    return (0);
}

int key_release(int keycode, void *param)
{
    t_mygame *game = (t_mygame *)param;
    if (keycode == 119) game->key_w = 0;
    if (keycode == 115) game->key_s = 0;
    if (keycode == 97)  game->key_a = 0;
    if (keycode == 100) game->key_d = 0;
    return (0);
}