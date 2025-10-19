/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:50:04 by tszymans          #+#    #+#             */
/*   Updated: 2025/10/19 14:33:56 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_myimg	*select_texture(t_myray *ray, t_mygame *game)
{
	t_myimg	*res;

	res = NULL;
	if (ray == NULL || game == NULL)
		return (res);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			res = &game->textures.west;
		else
			res = &game->textures.east;
		return (res);
	}
	if (ray->ray_dir_y > 0)
		res = &game->textures.north;
	else
		res = &game->textures.south;
	return (res);
}

static double	compute_wall_x(t_myray *ray, t_mygame *game)
{
	double	wall_x;

	wall_x = 0.0;
	if (ray == NULL || game == NULL)
		return (0.0);
	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	return (wall_x - floor(wall_x));
}

static void	calculate_texture_x(t_myray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)ray->tex->width);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->tex_x = ray->tex->width - ray->tex_x - 1;
	}
	else
	{
		if (ray->ray_dir_y < 0)
			ray->tex_x = ray->tex->width - ray->tex_x - 1;
	}
}

void	draw_textured_column(t_myray *ray, t_mygame *game, int x)
{
	int	y;

	ray->wall_x = compute_wall_x(ray, game);
	ray->tex = select_texture(ray, game);
	if (ray->tex == NULL || ray->tex->addr == NULL)
	{
		fallback_to_flat_color(ray, game, x);
		return ;
	}
	calculate_texture_x(ray);
	ray->tex_step = (double)ray->tex->height / (double)ray->line_height;
	ray->tex_pos = (ray->draw_start - game->scr_height / 2
			+ ray->line_height / 2) * ray->tex_step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		draw_tex_pixel(game, ray, x, y);
		y++;
	}
}
