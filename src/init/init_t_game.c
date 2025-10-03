/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:40:40 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/26 08:41:10 by tszymans         ###   ########.fr       */
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

char *test_map[10] = {
	"1111111111",
	"1000000001",
	"1000000001",
	"1001100001",
	"1001100001",
	"1000000001",
	"1000000001",
	"10N0000001",
	"1000000001",
	"1111111111"};

void allocate_map_grid(t_mygame *game)
{
	game->map.grid = malloc(sizeof(char *) * game->map.height);
	for (int y = 0; y < game->map.height; y++)
	{
		game->map.grid[y] = strdup(test_map[y]);
	}
}

void	init_game(t_mygame *game)
{
		// Reset keys pressed state
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
	
	
	// FOR TESTING PURPOSES
	// For testing: set up a simple 10x10 map
	// game->map.grid = test_map;
	// game->map.width = 10;
	// game->map.height = 10;
	game->scr_width = 1024;  // Set desired screen width
	game->scr_height = 512; // Set desired screen height
	
	allocate_map_grid(game);
	game->map.tile_size = 10; // Each tile is 10x10 pixels
	game->scr_height = 512;
	game->scr_width = 1024;
	game->prev_mouse_x = game->scr_width / 2;
	game->prev_mouse_y = game->scr_height / 2;
	printf("Mouse initial pos: x=%d y=%d\n", game->prev_mouse_x, game->prev_mouse_y);
	init_myconfig(game);
	

	// END FOR TESTING PURPOSES
}
