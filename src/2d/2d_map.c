/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:28:22 by tszymans          #+#    #+#             */
/*   Updated: 2025/10/16 14:41:06 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	t_draw_player_vars		v;
	char					*dst;

	v = init_draw_player_vars(game);
	while (v.i < game->player.player_size)
	{
		v.j = 0;
		while (v.j < game->player.player_size)
		{
			v.x = v.px + v.j;
			v.y = v.py + v.i;
			if (v.x >= 0 && v.x < game->map.width * game->map.tile_size
				&& v.y >= 0 && v.y < game->map.height * game->map.tile_size)
			{
				dst = game->img.addr + (v.y * game->img.line_len
						+ v.x * (game->img.bpp / 8));
				*(unsigned int *)dst = 0xFF0000;
			}
			v.j++;
		}
		v.i++;
	}
	draw_nose(game, &game->player, v.px, v.py);
	draw_mv_dir(game, &game->player, v.px, v.py);
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
				color = 0xFFFFFF;
			else if (cell == '0')
				color = 0xCCCCCC;
			else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
				color = 0xCCCCCC;
			else
				color = 0xFF00FF;
			draw_square(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_crosshair(t_mygame *game)
{
	int	dx;
	int	dy;
	int	ch_size;
	int	color;

	color = 0xFFFFFF;
	ch_size = 10;
	dx = -ch_size / 2;
	while (dx <= ch_size / 2)
	{
		draw_pixel_to_buffer(&game->img, game->scr_width / 2 + dx,
			game->scr_height / 2, color);
		dx++;
	}
	dy = -ch_size / 2;
	while (dy <= ch_size / 2)
	{
		draw_pixel_to_buffer(&game->img, game->scr_width / 2,
			game->scr_height / 2 + dy, color);
		dy++;
	}
}
