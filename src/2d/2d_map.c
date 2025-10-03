/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:28:22 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/27 12:14:34 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_pixel_to_buffer(t_myimg *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_square(t_myimg *img, int x, int y, int color, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			draw_pixel_to_buffer(img, x * size + j, y * size + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_nose(t_mygame *game, t_myplayer *player, int px, int py)
{
	int	nose_length;
	int	nx;
	int	ny;
	int	i;

	nose_length = player->player_size;
	i = 0;
	while (i < nose_length)
	{
		nx = (int)(px + player->player_size / 2 + player->dir_x * i);
		ny = (int)(py + player->player_size / 2 + player->dir_y * i);
		if (nx >= 0 && nx < game->map.width * game->map.tile_size
			&& ny >= 0 && ny < game->map.height * game->map.tile_size)
		{
			draw_pixel_to_buffer(&game->img, nx, ny, 0x000000);
		}
		i++;
	}
}

static void	draw_mv_dir(t_mygame *game, t_myplayer *player, int px, int py)
{
	int	mv_length;
	int	nx;
	int	ny;
	int	i;

	mv_length = player->player_size;
	i = 0;
	while (i < mv_length)
	{
		nx = (int)(px + player->player_size / 2 + player->mv_dir_x * i);
		ny = (int)(py + player->player_size / 2 + player->mv_dir_y * i);
		if (nx >= 0 && nx < game->map.width * game->map.tile_size
			&& ny >= 0 && ny < game->map.height * game->map.tile_size)
		{
			draw_pixel_to_buffer(&game->img, nx, ny, 0xFFFF00);
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

	px = (int)(game->player.x * game->map.tile_size
			- game->player.player_size / 2 - 1);
	py = (int)(game->player.y * game->map.tile_size
			- game->player.player_size / 2 - 1);
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
	draw_nose(game, &game->player, px, py);
	draw_mv_dir(game, &game->player, px, py);
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


void draw_crosshair(t_mygame *game)
{
	int dx;
	int dy;
	int ch_size;
	int color;
	
	color = 0xFFFFFF; // white
	ch_size = 10; // half size of crosshair
	dx = -ch_size/2;
	while (dx <= ch_size/2)
	{
		draw_pixel_to_buffer(&game->img, game->scr_width / 2 + dx, game->scr_height / 2, color);
		dx++;
	}
	dy = -ch_size/2;
	while (dy <= ch_size/2)
	{
		draw_pixel_to_buffer(&game->img, game->scr_width / 2, game->scr_height / 2 + dy, color);
		dy++;
	}
}
