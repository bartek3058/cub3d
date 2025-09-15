/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:28:22 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/15 10:42:37 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void draw_square(t_myimg *img, int x, int y, int color, int size)
{
	int		i;
	int		j;
	int		px;
	int		py;
	char	*dst;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			px = x * size + j;
			py = y * size + i;
			dst = img->addr + (py * img->line_len + px * (img->bpp / 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

void	draw_player(t_mygame *game)
{
	int x;
	int y;
	int px;
	int py;

	px = (int)(game->player.x * game->map.tile_size - game->player.player_size / 2 - 1);
	py = (int)(game->player.y * game->map.tile_size - game->player.player_size / 2 - 1);
	for (int i = 0; i < game->player.player_size; i++)
		for (int j = 0; j < game->player.player_size; j++)
		{
			x = px + j;
			y = py + i;
			if (x >= 0 && x < game->map.width * game->map.tile_size && y >= 0 && y < game->map.height * game->map.tile_size)
			{
				char *dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
				*(unsigned int *)dst = 0xFF0000;
			}
		}
	// Draw direction line ("nose")
	int nose_length = game->player.player_size; // length of the nose

	for (int i = 0; i < nose_length; i++)
	{
		int nx = (int)(px + game->player.player_size / 2 + game->player.dir_x * i);
		int ny = (int)(py + game->player.dir_y * i);
		if (nx >= 0 && nx < game->map.width * game->map.tile_size && ny >= 0 && ny < game->map.height * game->map.tile_size)
		{
			char *dst = game->img.addr + (ny * game->img.line_len + nx * (game->img.bpp / 8));
			*(unsigned int *)dst = 0x000000; // black
		}
	}
	// end testing
}

void	draw_2d_map(t_mygame *game)
{
	int		x;
	int		y;
	char	cell;
	int		color;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			cell = game->map.grid[y][x];
			if (cell == '1')
				color = 0xFFFFFF; // biały dla ścian
			else if (cell == '0')
				color = 0xCCCCCC; // szary dla przestrzeni
			else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
				color = 0xCCCCCC;
			else
				color = 0xFF00FF; // magenta dla innych znaków (błąd)
			draw_square(&game->img, x, y, color, game->map.tile_size);
			x++;
		}
		y++;
	}
}

// void   draw_all(t_mygame *game)
// {
//     draw_2d_map(game);
//     draw_player(game);
// }
