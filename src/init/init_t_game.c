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
	init_myconfig(game);
	/* initialize textures to safe defaults (avoid uninitialized memory) */
	game->textures.north.img = NULL;
	game->textures.north.addr = NULL;
	game->textures.north.bpp = 0;
	game->textures.north.line_len = 0;
	game->textures.north.endian = 0;
	game->textures.north.width = 0;
	game->textures.north.height = 0;
	game->textures.south.img = NULL;
	game->textures.south.addr = NULL;
	game->textures.south.bpp = 0;
	game->textures.south.line_len = 0;
	game->textures.south.endian = 0;
	game->textures.south.width = 0;
	game->textures.south.height = 0;
	game->textures.west.img = NULL;
	game->textures.west.addr = NULL;
	game->textures.west.bpp = 0;
	game->textures.west.line_len = 0;
	game->textures.west.endian = 0;
	game->textures.west.width = 0;
	game->textures.west.height = 0;
	game->textures.east.img = NULL;
	game->textures.east.addr = NULL;
	game->textures.east.bpp = 0;
	game->textures.east.line_len = 0;
	game->textures.east.endian = 0;
	game->textures.east.width = 0;
	game->textures.east.height = 0;
}

int load_texture(t_mygame *game, t_myimg *img, char *path)
{
	int img_width;
	int img_height;

	img_width = 0;
	img_height = 0;
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
	img->width = img_width;
	img->height = img_height;
	return (1);
}

int load_textures(t_mygame *game)
{
	if (!game->config.tex_no || !game->config.tex_so
		|| !game->config.tex_we || !game->config.tex_ea)
		return (0);
	if (!load_texture(game, &game->textures.north, game->config.tex_no))
		return (0);
	if (!load_texture(game, &game->textures.south, game->config.tex_so))
		return (0);
	if (!load_texture(game, &game->textures.west, game->config.tex_we))
		return (0);
	if (!load_texture(game, &game->textures.east, game->config.tex_ea))
		return (0);
	return (1);
}
