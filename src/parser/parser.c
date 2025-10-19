/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:19:41 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/19 17:42:00 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parser(char **argv, t_mygame *game)
{
	char		**lines;
	int			map_start;
	t_parse_ctx	ctx;

	lines = load_map(game, argv[1]);
	map_start = parse_config(lines, game);
	check_config(lines, game);
	init_map(game, lines, map_start);
	ctx.game = game;
	ctx.lines = lines;
	parse_map(ctx, game);
	check_trailing_lines(lines, map_start + game->map.height - 1, game);
	free_split(lines);
}

int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	handle_tile(t_parse_ctx *ctx, int i, int j, int *player_found)
{
	char	c;

	c = ctx->game->map.grid[i][j];
	if (c == '1' || c == '0' || c == ' ')
		return (0);
	if (is_player_char(c))
	{
		if (*player_found == 1)
			map_parse_error(ctx, "Error: multiple player positions");
		*player_found = 1;
		ctx->game->player.x = j + 0.5;
		ctx->game->player.y = i + 0.5;
		set_player_direction(&ctx->game->player, c);
		ctx->game->map.grid[i][j] = '0';
		return (0);
	}
	if (!is_player_char(c) && c != '1' && c != '0' && c != ' '
		&& c != '\n' && c != '\r' && c != '\0')
	{
		map_parse_error(ctx, "Error: invalid character in map");
	}
	return (0);
}

void	flood_check(char **lines, t_mygame *game, int y, int x)
{
	char	**grid;

	grid = game->map.grid;
	if (y < 0 || y >= game->map.height || x < 0 || x >= (int)ft_strlen(grid[y]))
	{
		free_split(lines);
		free_myconfig(&game->config);
		free_map_grid(game);
		exit_error("Error: map not closed (edge)");
	}
	if (grid[y][x] == ' ')
	{
		free_split(lines);
		free_myconfig(&game->config);
		free_map_grid(game);
		exit_error("Error: map not closed (space hole)");
	}
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	grid[y][x] = 'V';
	flood_check(lines, game, y - 1, x);
	flood_check(lines, game, y + 1, x);
	flood_check(lines, game, y, x - 1);
	flood_check(lines, game, y, x + 1);
}

int	parse_map(t_parse_ctx ctx, t_mygame *game)
{
	int			i;
	int			j;
	int			player_found;

	player_found = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (handle_tile(&ctx, i, j, &player_found) == 1)
				return (1);
			else if (game->map.grid[i][j] == '\n' ||
				game->map.grid[i][j] == '\0')
				break ;
			j++;
		}
		i++;
	}
	if (player_found == 0)
		map_parse_error(&ctx, "Error: no player position found");
	validate_map_closed(ctx.lines, ctx.game);
	return (0);
}
