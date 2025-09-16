/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:49:21 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/16 09:50:32 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	close_hook(void *param)
{
    t_mygame *game = (t_mygame *)param;
    mlx_loop_end(game->mlx);
	return (1);
}

int key_press(int keycode, void *param)
{
	t_mygame *game = (t_mygame *)param;

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
		mlx_loop_end(game->mlx); // ESC key
	return (0);
}

int key_release(int keycode, void *param)
{
	t_mygame *game = (t_mygame *)param;

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
