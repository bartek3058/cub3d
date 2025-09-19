/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:55:05 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/19 10:06:47 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	raycaster(t_myray *ray, t_mygame *game)
{
	int	x;

	x = 0;
	while (x < game->scr_width)
	{
		ray->cam_x = 2 * x / (double)game->scr_width - 1; // x-coord in camera space
		ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->cam_x;
		ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->cam_x;

		x++;
	}
}
