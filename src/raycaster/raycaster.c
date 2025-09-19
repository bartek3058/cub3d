/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:55:05 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/19 11:02:38 by tszymans         ###   ########.fr       */
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

static void	DDA(t_myray *ray, t_mygame *game)
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
		// sprawdzenie czy ray trafił w ścianę
		if (game->map.grid[ray->map_x][ray->map_y] > 0)
			ray->hit = 1;
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
		initial_side_dist(ray, game);
		DDA(ray, game);
		x++;
	}
}
