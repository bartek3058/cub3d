/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:40:40 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/24 09:19:26 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_mygame *game)
{
//	game->player.x = 1.5;			// Default X position
//	game->player.y = 1.5;			// Default Y position
	// game->player.dir_x = 1;		// Facing right
	// game->player.dir_y = 0;
	// game->player.plane_x = 0;	// 2D raycaster camera plane
	// game->player.plane_y = 0.66;	// FOV 66 degrees
	game->player.mv_spd = 0.01;	// Movement speed
	game->player.rot_spd = 0.002;	// Rotation speed
	game->player.player_size = 5;	// Player size in pixels
	game->player.angle = atan2(game->player.dir_y, game->player.dir_x);
}
