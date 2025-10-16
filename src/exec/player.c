/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:50:04 by tszymans          #+#    #+#             */
/*   Updated: 2025/10/16 14:50:19 by brogalsk         ###   ########.fr       */
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

void	rotate_player(t_mygame *game)
{
	game->player.mv_dir_x = game->player.dir_x;
	game->player.mv_dir_y = game->player.dir_y;
	printf("Rotated player to dir: (%.2f, %.2f); angle: %.2f\n",
		game->player.dir_x, game->player.dir_y, game->player.angle);
	printf("Player plane to: (%.2f, %.2f)\n",
		game->player.plane_x, game->player.plane_y);
	printf("Player move to: (%.2f, %.2f)\n",
		game->player.mv_dir_x, game->player.mv_dir_y);
}

void	rotate_camera(t_mygame *game, double angle)
{
	update_camera_vectors(&game->player, angle);
	game->player.angle = fmod(game->player.angle + angle, 2 * 3.14159);
	if (game->player.angle < 0)
		game->player.angle += 2 * 3.14159;
	printf("Rotated player to dir: (%.2f, %.2f); angle: %.2f\n",
		game->player.dir_x, game->player.dir_y, game->player.angle);
	printf("Player plane to: (%.2f, %.2f)\n",
		game->player.plane_x, game->player.plane_y);
	printf("Player move to: (%.2f, %.2f)\n",
		game->player.mv_dir_x, game->player.mv_dir_y);
}

void	update_player_controls(t_mygame *game)
{
	if (game->key_a)
	{
		rotate_camera(game, -game->player.rot_spd);
		rotate_player(game);
	}
	if (game->key_d)
	{
		rotate_camera(game, game->player.rot_spd);
		rotate_player(game);
	}
	if (game->key_w)
		move_player(
			game, game->player.x + game->player.mv_dir_x * game->player.mv_spd,
			game->player.y + game->player.mv_dir_y * game->player.mv_spd);
	if (game->key_s)
		move_player(
			game, game->player.x - game->player.mv_dir_x * game->player.mv_spd,
			game->player.y - game->player.mv_dir_y * game->player.mv_spd);
	if (game->key_left_arrow)
		rotate_camera(game, -game->player.rot_spd);
	if (game->key_right_arrow)
		rotate_camera(game, game->player.rot_spd);
}
