/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:50:04 by tszymans          #+#    #+#             */
/*   Updated: 2025/10/19 14:10:36 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	fallback_to_flat_color(t_myray *ray, t_mygame *game, int x)
{
	int	color;
	int	y;

	color = 0xFF0000;
	if (ray->side == 1)
		darker_color(&color, 0.7);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		draw_pixel_to_buffer(&game->img, x, y, color);
		y++;
	}
}

/* helper: read a pixel from texture safely */
int	tex_get_pixel(t_myimg *tex, int tx, int ty)
{
	char	*ptr;
	int		pix;

	ptr = NULL;
	pix = 0xFF00FF;
	if ((tex == NULL) || (tex->addr == NULL) || (tx < 0) || (tx >= tex->width)
		|| (ty < 0) || (ty >= tex->height))
		return (pix);
	ptr = tex->addr + (ty * tex->line_len + tx * (tex->bpp / 8));
	pix = (*(int *)ptr);
	return (pix);
}

/* helper: sample texture, shade if needed and draw single pixel row */
void	draw_tex_pixel(t_mygame *game, t_myray *ray, int x, int y)
{
	unsigned int	color;
	int				c;

	ray->tex_y = (int)(ray->tex_pos);
	if (ray->tex_y < 0)
		ray->tex_y = 0;
	if (ray->tex_y >= ray->tex->height)
		ray->tex_y = ray->tex->height - 1;
	color = tex_get_pixel(ray->tex, ray->tex_x, ray->tex_y);
	if (ray->side == 1)
	{
		c = (int)color;
		darker_color(&c, 0.7);
		color = (unsigned int)c;
	}
	draw_pixel_to_buffer(&game->img, x, y, color);
	ray->tex_pos += ray->tex_step;
}
