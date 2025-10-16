/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:00:13 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/16 15:00:29 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	free_myconfig(t_myconfig *cfg)
{
	free(cfg->tex_no);
	free(cfg->tex_so);
	free(cfg->tex_we);
	free(cfg->tex_ea);
}

void	free_map_grid(t_mygame *game)
{
	int	y;

	if (!game->map.grid)
		return ;
	y = 0;
	while (y < game->map.height)
	{
		free(game->map.grid[y]);
		y++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}
