/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:40:40 by tszymans          #+#    #+#             */
/*   Updated: 2025/10/16 18:03:48 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_myconfig(t_mygame *game)
{
	game->config.tex_no = NULL;
	game->config.tex_so = NULL;
	game->config.tex_we = NULL;
	game->config.tex_ea = NULL;
	game->config.floor_color = -1;
	game->config.ceil_color = -1;
}

//void	allocate_map_grid(t_mygame *game)
//{
//	int	y;

//	if (game->map.height <= 0)
//		return ;
//	y = 0;
//	game->map.grid = malloc(sizeof(char *) * game->map.height);
//	if (!game->map.grid)
//		exit_error("Error: malloc failed for map grid");
//	while (y < game->map.height)
//	{
//		game->map.grid[y] = ft_strdup(test_map[y]);
//		if (!game->map.grid[y])
//		{
//			free_map_grid(game);
//			exit_error("Error: malloc failed for map row");
//		}
//		y++;
//	}
//}

void	init_game(t_mygame *game)
{
	game->key_w = 0;
	game->key_s = 0;
	game->key_a = 0;
	game->key_d = 0;
	game->key_left_arrow = 0;
	game->key_right_arrow = 0;
	game->key_esc = 0;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->scr_width = 1024;
	game->scr_height = 512;
	game->map.tile_size = 10;
	game->scr_height = 512;
	game->scr_width = 1024;
	game->prev_mouse_x = game->scr_width / 2;
	game->prev_mouse_y = game->scr_height / 2;
	printf("Mouse initial pos: x=%d y=%d\n",
		game->prev_mouse_x, game->prev_mouse_y);
	init_myconfig(game);
}
