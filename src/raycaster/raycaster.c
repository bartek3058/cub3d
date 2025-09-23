/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:55:05 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/23 10:40:59 by tszymans         ###   ########.fr       */
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
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
	}
}

static void	dda(t_myray *ray, t_mygame *game)
{
	// implementacja DDA
	while (ray->hit == 0)
	{
		// skok w x lub y
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
		// BOUNDS CHECK
		if (ray->map_x < 0 || ray->map_x >= game->map.width
			|| ray->map_y < 0 || ray->map_y >= game->map.height)
		{
			ray->hit = 1; // treat as hit (outside map)
			return ;
		}
		// sprawdzenie czy ray trafił w ścianę
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	draw_line(t_myray *ray, t_mygame *game, int x)
{
	int		color;
	int		y;

	color = 0xFF0000; // domyślny kolor ściany (czerwony)
	ray->line_height = (int)(game->scr_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->scr_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->scr_height / 2;
	if (ray->draw_end >= game->scr_height)
		ray->draw_end = game->scr_height - 1;
	if (ray->side == 1)
	{
		//color = color / 2; // ciemniejszy odcień dla ścian pionowych
		int r = ((color >> 16) & 0xFF) * 0.7;
		int g = ((color >> 8) & 0xFF) * 0.7;
		int b = (color & 0xFF) * 0.7;
		color = (r << 16) | (g << 8) | b;
	}
	// Rysowanie pionowej linii
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		draw_pixel_to_buffer(&game->img, x, y, color);
		y++;
	}
}

void	raycaster(t_myray *ray, t_mygame *game)
{
	int	x;

	x = 0;
	while (x < game->scr_width)
	{
		ray->cam_x = 2 * x / (double)game->scr_width - 1; //x-coord in cam space
		ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->cam_x;
		ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->cam_x;
		ray->map_x = (int)game->player.x;
		ray->map_y = (int)game->player.y;
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
		ray->hit = 0;
		initial_side_dist(ray, game);
		dda(ray, game);
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
		else
			ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
		draw_line(ray, game, x);
		x++;
	}
}
