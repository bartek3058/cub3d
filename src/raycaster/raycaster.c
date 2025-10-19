/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:55:05 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/24 09:21:48 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	initial_side_dist(t_myray *ray, t_mygame *game)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

static void	dda(t_myray *ray, t_mygame *game)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= game->map.width
			|| ray->map_y < 0 || ray->map_y >= game->map.height)
		{
			ray->hit = 1;
			return ;
		}
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

int	darker_color(int *color, double factor)
{
	int	r;
	int	g;
	int	b;

	r = ((*color >> 16) & 0xFF) * factor;
	g = ((*color >> 8) & 0xFF) * factor;
	b = (*color & 0xFF) * factor;
	*color = (r << 16) | (g << 8) | b;
	return (*color);
}

static void	pre_raycaster(t_myray *ray, t_mygame *game, int x)
{
	ray->cam_x = 2 * x / (double)game->scr_width - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->cam_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->cam_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	ray->hit = 0;
}

void	raycaster(t_myray *ray, t_mygame *game)
{
	int	x;

	x = 0;
	while (x < game->scr_width)
	{
		pre_raycaster(ray, game, x);
		initial_side_dist(ray, game);
		dda(ray, game);
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
		else
			ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
		ray->line_height = (int)(game->scr_height / ray->perp_wall_dist);
		ray->draw_start = -ray->line_height / 2 + game->scr_height / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + game->scr_height / 2;
		if (ray->draw_end >= game->scr_height)
			ray->draw_end = game->scr_height - 1;
		draw_textured_column(ray, game, x);
		x++;
	}
}
