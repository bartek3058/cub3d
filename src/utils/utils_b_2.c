/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:30:17 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/16 17:33:37 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_trailing_lines(char **lines, int map_end_index, t_mygame *game)
{
	int	i;

	i = map_end_index + 1;
	while (lines[i])
	{
		if (!is_blank(lines[i]))
		{
			free_split(lines);
			free_myconfig(&game->config);
			free_map_grid(game);
			exit_error("Invalid character(s) after map");
		}
		i++;
	}
}

static void	exit_missing_texture(char **lines, t_mygame *game, const char *msg)
{
	free_split(lines);
	free_myconfig(&game->config);
	free_map_grid(game);
	printf("Missing %s path\n", msg);
	exit(EXIT_FAILURE);
}

static void	check_textures(char **lines, t_mygame *game)
{
	if (game->config.tex_no == NULL)
		exit_missing_texture(lines, game, "NO");
	if (game->config.tex_so == NULL)
		exit_missing_texture(lines, game, "SO");
	if (game->config.tex_we == NULL)
		exit_missing_texture(lines, game, "WE");
	if (game->config.tex_ea == NULL)
		exit_missing_texture(lines, game, "EA");
}

static void	check_colors(char **lines, t_mygame *game)
{
	if (game->config.floor_color == -1)
	{
		free_split(lines);
		free_myconfig(&game->config);
		free_map_grid(game);
		printf("Missing floor color\n");
		exit(EXIT_FAILURE);
	}
	if (game->config.ceil_color == -1)
	{
		free_split(lines);
		free_myconfig(&game->config);
		free_map_grid(game);
		printf("Missing ceil color\n");
		exit(EXIT_FAILURE);
	}
}

void	check_config(char **lines, t_mygame *game)
{
	check_textures(lines, game);
	check_colors(lines, game);
}
