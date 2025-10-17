/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:57:06 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/16 16:58:20 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_direction_north(t_myplayer *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

static void	set_direction_south(t_myplayer *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -0.66;
	player->plane_y = 0;
}

static void	set_direction_east(t_myplayer *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

static void	set_direction_west(t_myplayer *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
}

void	set_player_direction(t_myplayer *player, char dir)
{
	if (dir == 'N')
	{
		set_direction_north(player);
	}
	else if (dir == 'S')
	{
		set_direction_south(player);
	}
	else if (dir == 'E')
	{
		set_direction_east(player);
	}
	else if (dir == 'W')
	{
		set_direction_west(player);
	}
	player->mv_dir_x = player->dir_x;
	player->mv_dir_y = player->dir_y;
}
