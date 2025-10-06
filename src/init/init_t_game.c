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

	// END FOR TESTING PURPOSES
}

int	load_texture(t_mygame *game, t_myimg *img, char *path)
{
	int img_width;
	int img_height;

	img_width = 64;
	img_height = 64;
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img_width, &img_height);
	if (!img->img)
	{
		fprintf(stderr, "Error loading texture from %s\n", path);
		return (0);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
	{
		fprintf(stderr, "Error getting data address for texture %s\n", path);
		return (0);
	}
	return (1);
}
int load_textures(t_mygame *game)
{
	printf("Loading texture: %s\n", game->config.tex_no);
	if (!game->config.tex_no || !load_texture(game, &game->textures.north, game->config.tex_no))
	{
		fprintf(stderr, "Failed to load north texture\n");
		exit(EXIT_FAILURE);
	}
	if (!game->config.tex_so || !load_texture(game, &game->textures.south, game->config.tex_so))
	{
		fprintf(stderr, "Failed to load south texture\n");
		exit(EXIT_FAILURE);
	}
	if (!game->config.tex_ea || !load_texture(game, &game->textures.east, game->config.tex_ea))
	{
		fprintf(stderr, "Failed to load east texture\n");
		exit(EXIT_FAILURE);
	}
	if (!game->config.tex_we || !load_texture(game, &game->textures.west, game->config.tex_we))
	{
		fprintf(stderr, "Failed to load west texture\n");
		exit(EXIT_FAILURE);
	}
	return 1;
}
