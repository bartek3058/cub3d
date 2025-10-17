/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:24:29 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/17 10:43:02 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_draw_player_vars	init_draw_player_vars(t_mygame *game)
{
	t_draw_player_vars	v;

	v.px = (int)(game->player.x * game->map.tile_size
			- game->player.player_size / 2 - 1);
	v.py = (int)(game->player.y * game->map.tile_size
			- game->player.player_size / 2 - 1);
	v.i = 0;
	return (v);
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

void	draw_pixel_to_buffer(t_myimg *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_mygame *game, int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map.tile_size - 1)
	{
		j = 0;
		while (j < game->map.tile_size - 1)
		{
			draw_pixel_to_buffer(&game->img,
				x * game->map.tile_size + j,
				y * game->map.tile_size + i, color);
			j++;
		}
		i++;
	}
}
