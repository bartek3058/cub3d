/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:24:29 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/16 14:41:39 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_draw_player_vars	init_draw_player_vars(t_mygame *game)
{
	t_draw_player_vars	v;

	v.px = (int)(game->player.x * game->map.tile_size
			- game->player.player_size / 2 - 1);
	v.py = (int)(game->player.y * game->map.tile_size
			- game->player.player_size / 2 - 1);
	v.i = 0;
	return (v);
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
