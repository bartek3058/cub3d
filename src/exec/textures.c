/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:50:04 by tszymans          #+#    #+#             */
/*   Updated: 2025/10/16 14:50:19 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* helper: read a pixel from texture safely */
static unsigned int tex_get_pixel(t_myimg *tex, int tx, int ty)
{
	char            *ptr;
	unsigned int    pix;

	ptr = NULL;
	pix = 0xFF00FF;
	if (tex == NULL)
	{
		return (pix);
	}
	if (tex->addr == NULL)
	{
		return (pix);
	}
	if (tx < 0)
	{
		return (pix);
	}
	if (tx >= tex->width)
	{
		return (pix);
	}
	if (ty < 0)
	{
		return (pix);
	}
	if (ty >= tex->height)
	{
		return (pix);
	}
	ptr = tex->addr + (ty * tex->line_len + tx * (tex->bpp / 8));
	pix = (*(unsigned int *)ptr);
	return (pix);
}

/* select correct texture for this hit */
static t_myimg
*select_texture(t_myray *ray, t_mygame *game)
{
	t_myimg *res;

	res = NULL;
	if (ray == NULL || game == NULL)
	{
		return (res);
	}
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
		{
			res = &game->textures.west;
		}
		else
		{
			res = &game->textures.east;
		}
		return (res);
	}
	if (ray->ray_dir_y > 0)
	{
		res = &game->textures.north;
	}
	else
	{
		res = &game->textures.south;
	}
	return (res);
}

/* compute fractional wall hit position (0..1) */
static double
compute_wall_x(t_myray *ray, t_mygame *game)
{
	double  wall_x;

	wall_x = 0.0;
	if (ray == NULL || game == NULL)
	{
		return (0.0);
	}
	if (ray->side == 0)
	{
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	return (wall_x - floor(wall_x));
}

/* draw textured vertical stripe at screen column x */
void
draw_textured_column(t_myray *ray, t_mygame *game, int x)
{
	int         line_height;
	int         draw_start;
	int         draw_end;
	double      wall_x;
	t_myimg     *tex;
	int         tex_x;
	double      step;
	double      tex_pos;
	int         y;

	line_height = ray->line_height;
	draw_start = ray->draw_start;
	draw_end = ray->draw_end;
	wall_x = compute_wall_x(ray, game);
	tex = select_texture(ray, game);
	if (tex == NULL)
	{
		/* fallback to flat color */
		int color;
		color = 0xFF0000;
		if (ray->side == 1)
		{
			darker_color(&color, 0.7);
		}
		y = draw_start;
		while (y < draw_end)
		{
			draw_pixel_to_buffer(&game->img, x, y, color);
			y++;
		}
		return;
	}
	if (tex->addr == NULL)
	{
		/* fallback to flat color */
		int color;

		color = 0xFF0000;
		if (ray->side == 1)
		{
			darker_color(&color, 0.7);
		}
		y = draw_start;
		while (y < draw_end)
		{
			draw_pixel_to_buffer(&game->img, x, y, color);
			y++;
		}
		return;
	}

	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
		{
			tex_x = tex->width - tex_x - 1;
		}
	}
	else
	{
		if (ray->ray_dir_y < 0)
		{
			tex_x = tex->width - tex_x - 1;
		}
	}

	step = (double)tex->height / (double)line_height;
	tex_pos = (draw_start - game->scr_height / 2 + line_height / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		int tex_y;
		unsigned int color;
		int c;

		tex_y = (int)tex_pos;
		if (tex_y < 0)
		{
			tex_y = 0;
		}
		if (tex_y >= tex->height)
		{
			tex_y = tex->height - 1;
		}
		color = tex_get_pixel(tex, tex_x, tex_y);
		if (ray->side == 1)
		{
			c = (int)color;
			darker_color(&c, 0.7);
			color = (unsigned int)c;
		}
		draw_pixel_to_buffer(&game->img, x, y, color);
		tex_pos += step;
		y++;
	}
}
