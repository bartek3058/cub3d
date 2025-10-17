/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:01:52 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/16 15:04:58 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_image(t_mygame *game, int width, int height)
{
	game->img.img = mlx_new_image(game->mlx, width, height);
	if (!game->img.img)
		return (1);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	if (!game->img.addr)
		return (1);
	return (0);
}

static int	get_map_width(char **lines)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max - 1);
}

void	init_map(t_mygame *game, char **lines, int a)
{
	int	i;

	i = 0;
	game->map.height = 0;
	while (lines[a + game->map.height]
		&& !is_blank(lines[a + game->map.height]))
		game->map.height++;
	game->map.width = get_map_width(&lines[a]);
	printf("Map dimensions: width=%d, height=%d\n",
		game->map.width, game->map.height);
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return ;
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_strdup(lines[a]);
		a++;
		i++;
	}
	game->map.grid[i] = NULL;
}

void	init_myconfig(t_mygame *game)
{
	game->config.tex_no = NULL;
	game->config.tex_so = NULL;
	game->config.tex_we = NULL;
	game->config.tex_ea = NULL;
	game->config.floor_color = -1;
	game->config.ceil_color = -1;
}
