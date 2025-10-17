/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:49:21 by tszymans          #+#    #+#             */
/*   Updated: 2025/10/16 14:54:30 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	close_hook(t_mygame *game)
{
	mlx_loop_end(game->mlx);
	return (1);
}

int	key_press(int keycode, t_mygame *game)
{
	if (keycode == 119)
		game->key_w = 1;
	if (keycode == 115)
		game->key_s = 1;
	if (keycode == 97)
		game->key_a = 1;
	if (keycode == 100)
		game->key_d = 1;
	if (keycode == 65361)
		game->key_left_arrow = 1;
	if (keycode == 65363)
		game->key_right_arrow = 1;
	if (keycode == 65307)
		mlx_loop_end(game->mlx);
	return (0);
}

int	key_release(int keycode, t_mygame *game)
{
	if (keycode == 119)
		game->key_w = 0;
	if (keycode == 115)
		game->key_s = 0;
	if (keycode == 97)
		game->key_a = 0;
	if (keycode == 100)
		game->key_d = 0;
	if (keycode == 65361)
		game->key_left_arrow = 0;
	if (keycode == 65363)
		game->key_right_arrow = 0;
	return (0);
}

int	mouse_move(int x, int y, t_mygame *game)
{
	int	delta_x;

	if (x < 0 || x >= game->scr_width || game->prev_mouse_x < 0
		|| game->prev_mouse_x >= game->scr_width)
		return (0);
	delta_x = x - game->prev_mouse_x;
	(void)y;
	if (delta_x != 0)
	{
		rotate_camera(game, delta_x * game->player.rot_spd * 2);
	}
	game->prev_mouse_x = x;
	return (0);
}

void	update_camera_vectors(t_myplayer *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y
		* sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}
