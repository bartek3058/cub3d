/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:04:23 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/16 17:05:28 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	map_parse_error(t_parse_ctx *ctx, char *msg)
{
	free_split(ctx->lines);
	free_myconfig(&ctx->game->config);
	free_map_grid(ctx->game);
	exit_error(msg);
}

static void	check_map_closure(char **lines, t_mygame *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == '0'
				|| is_player_char(game->map.grid[y][x]))
				flood_check(lines, game, y, x);
			x++;
		}
		y++;
	}
}

static void	reset_visited_tiles(t_mygame *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'V')
				game->map.grid[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	validate_map_closed(char **lines, t_mygame *game)
{
	check_map_closure(lines, game);
	reset_visited_tiles(game);
}

int	starts_with_token(const char *s, const char *tok)
{
	int	i;
	int	j;

	if (!s || !tok)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	j = 0;
	while (tok[j] && s[i + j] && s[i + j] == tok[j])
		j++;
	if (tok[j] != '\0')
		return (0);
	if (s[i + j] == ' ' || s[i + j] == '\t' || s[i + j] == '\0')
		return (1);
	return (0);
}
