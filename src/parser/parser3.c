/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:00:10 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/16 17:03:18 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_config_line(char *line)
{
	if (!line || is_blank(line))
		return (0);
	if (starts_with_token(line, "NO") || starts_with_token(line, "SO")
		|| starts_with_token(line, "WE") || starts_with_token(line, "EA")
		|| starts_with_token(line, "F") || starts_with_token(line, "C"))
		return (1);
	return (0);
}

int	parse_color(char *str, char **lines, char **parts, t_mygame *game)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		free_split(lines);
		free_split(rgb);
		free_myconfig(&game->config);
		free_map_grid(game);
		free_split(parts);
		exit_error("Invalid color: missing R,G or B value");
	}
	r = parse_single_color_component(rgb[0], lines, rgb, game, parts);
	g = parse_single_color_component(rgb[1], lines, rgb, game, parts);
	b = parse_single_color_component(rgb[2], lines, rgb, game, parts);
	check_color(r, g, b, lines, rgb, parts, game);
	color = (r << 16) | (g << 8) | b;
	free_split(rgb);
	return (color);
}

static char	**smart_split_config(char *line)
{
	char	**parts;
	int		i;
	int		start;

	parts = malloc(sizeof(char *) * 3);
	if (!parts)
		return (NULL);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	parts[0] = ft_substr(line, start, i - start);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	parts[1] = ft_strdup(line + i);
	parts[2] = NULL;
	return (parts);
}

static void	save_config_line(t_mygame *game, char *line, char **lines)
{
	char	**parts;

	parts = smart_split_config(line);
	if (!parts || !parts[0] || !parts[1])
		exit_error("Invalid config line");
	save_texture(game, parts[0], parts[1], lines, parts);
	save_color(game, parts[0], parts[1], lines, parts);
	free_split(parts);
}

int	parse_config(char **lines, t_mygame *game)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_blank(lines[i]))
		{
			i++;
			continue ;
		}
		if (is_config_line(lines[i]))
		{
			save_config_line(game, lines[i], lines);
			i++;
			continue ;
		}
		break ;
	}
	return (i);
}
