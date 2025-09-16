/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:50:04 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/16 10:17:06 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_move_valid(t_mygame *game, double new_x_pos, double new_y_pos)
{
	if (new_x_pos < 0 || new_y_pos < 0
		|| new_x_pos >= game->map.width || new_y_pos >= game->map.height)
		return (0);
	if (new_x_pos == game->player.x && new_y_pos == game->player.y)
		return (0);
	if (game->map.grid[(int)new_y_pos][(int)new_x_pos] == '1')
		return (0);
	return (1);
}

void	move_player(t_mygame *game, double new_x_pos, double new_y_pos)
{
	if (!is_move_valid(game, new_x_pos, new_y_pos))
		return ;
	game->player.x = new_x_pos;
	game->player.y = new_y_pos;
	draw_player(game);
}

void	rotate_player(t_mygame *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x
		= game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y
		= old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x
		= game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y
		= old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
	game->player.angle = fmod(game->player.angle + angle, 2 * 3.14159);
	if (game->player.angle < 0)
		game->player.angle += 2 * 3.14159;
	printf("Rotated player to dir: (%.2f, %.2f); angle: %.2f\n",
		game->player.dir_x, game->player.dir_y, game->player.angle);
}

void	update_player_controls(t_mygame *game)
{
	if (game->key_a)
		rotate_player(game, -game->player.rot_speed);
	if (game->key_d)
		rotate_player(game, game->player.rot_speed);
	if (game->key_w)
		move_player(game, game->player.x + game->player.dir_x * game->player.move_speed,
			game->player.y + game->player.dir_y * game->player.move_speed);
	if (game->key_s)
		move_player(game, game->player.x - game->player.dir_x * game->player.move_speed,
			game->player.y - game->player.dir_y * game->player.move_speed);
	// if (game->key_left_arrow)
	// 	rotate_player(game, -game->player.rot_speed);
	// if (game->key_right_arrow)
	// 	rotate_player(game, game->player.rot_speed);
}