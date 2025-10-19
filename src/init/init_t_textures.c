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

static void	init_texture_north(t_mygame *game)
{
	game->textures.north.img = NULL;
	game->textures.north.addr = NULL;
	game->textures.north.bpp = 0;
	game->textures.north.line_len = 0;
	game->textures.north.endian = 0;
	game->textures.north.width = 0;
	game->textures.north.height = 0;
}

static void	init_texture_south(t_mygame *game)
{
	game->textures.south.img = NULL;
	game->textures.south.addr = NULL;
	game->textures.south.bpp = 0;
	game->textures.south.line_len = 0;
	game->textures.south.endian = 0;
	game->textures.south.width = 0;
	game->textures.south.height = 0;
}

static void	init_texture_west(t_mygame *game)
{
	game->textures.west.img = NULL;
	game->textures.west.addr = NULL;
	game->textures.west.bpp = 0;
	game->textures.west.line_len = 0;
	game->textures.west.endian = 0;
	game->textures.west.width = 0;
	game->textures.west.height = 0;
}

static void	init_texture_east(t_mygame *game)
{
	game->textures.east.img = NULL;
	game->textures.east.addr = NULL;
	game->textures.east.bpp = 0;
	game->textures.east.line_len = 0;
	game->textures.east.endian = 0;
	game->textures.east.width = 0;
	game->textures.east.height = 0;
}

void init_textures(t_mygame *game)
{
	/* initialize textures to safe defaults (avoid uninitialized memory) */

	init_texture_north(game);
	init_texture_south(game);
	init_texture_west(game);
	init_texture_east(game);
}
