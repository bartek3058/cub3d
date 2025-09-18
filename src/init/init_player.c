/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:40:40 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/17 09:43:31 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player_from_map(t_mygame *game)
{
	int		x;
	int		y;
	char	cell;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			cell = game->map.grid[y][x];
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
				game->map.grid[y][x] = '0';			// Remove player marker from map
				game->player.mv_spd = 0.01;	// Set a default move speed
				game->player.rot_spd = 0.01;		// Set a default rotation speed
				game->player.player_size = 5;		// Set player size in pixels
				game->player.angle = atan2(game->player.dir_y, game->player.dir_x);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_mygame *game)
{
	game->player.x = 1.5;			// Default X position
	game->player.y = 1.5;			// Default Y position
	game->player.dir_x = 1;		// Facing right
	game->player.dir_y = 0;
	game->player.plane_x = 0;	// 2D raycaster camera plane
	game->player.plane_y = 0.66;	// FOV 66 degrees
	game->player.mv_spd = 0.01;	// Movement speed
	game->player.rot_spd = 0.01;	// Rotation speed
	game->player.player_size = 5;	// Player size in pixels
	game->player.angle = atan2(game->player.dir_y, game->player.dir_x);
}
