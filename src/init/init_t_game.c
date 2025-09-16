/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:40:40 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/16 10:15:56 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

	// FOR TESTING PURPOSES
	// For testing: set up a simple 10x10 map
	game->map.grid = test_map;
	game->map.width = 10;
	game->map.height = 10;

	allocate_map_grid(game);
	game->map.tile_size = 10; // Each tile is 10x10 pixels


	// END FOR TESTING PURPOSES
}