/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:00:10 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/16 18:02:39 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_config_line(char *line)
{
	if (!line || is_blank(line))
		return (0);
	if (starts_with_token(line, "NO") || starts_with_token(line, "SO")
		|| starts_with_token(line, "WE") || starts_with_token(line, "EA")
		|| starts_with_token(line, "F") || starts_with_token(line, "C"))
		return (1);
	return (0);
}

static void	free_color_ctx(t_color_ctx *ctx)
{
	free_split(ctx->lines);
	free_split(ctx->rgb);
	free_split(ctx->parts);
	free_map_grid(ctx->game);
	free_myconfig(&ctx->game->config);
}

int	parse_color(char *str, char **lines, char **parts, t_mygame *game)
{
	t_color_ctx	ctx;
	int			r;
	int			g;
	int			b;
	int			color;

	ctx.lines = lines;
	ctx.parts = parts;
	ctx.game = game;
	ctx.rgb = ft_split(str, ',');
	if (!ctx.rgb || !ctx.rgb[0] || !ctx.rgb[1] || !ctx.rgb[2])
	{
		free_color_ctx(&ctx);
		exit_error("Invalid color: missing R,G or B value");
	}
	r = parse_single_color_component(&ctx, ctx.rgb[0]);
	g = parse_single_color_component(&ctx, ctx.rgb[1]);
	b = parse_single_color_component(&ctx, ctx.rgb[2]);
	check_color(&ctx, r, g, b);
	color = (r << 16) | (g << 8) | b;
	free_split(ctx.rgb);
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

void	save_config_line(t_mygame *game, char *line, char **lines)
{
	char			**parts;
	t_parse_ctx		ctx;

	ctx.game = game;
	ctx.lines = lines;
	parts = smart_split_config(line);
	if (!parts || !parts[0] || !parts[1])
		exit_error("Invalid config line");
	save_texture(&ctx, parts[0], parts[1], parts);
	save_color(&ctx, parts[0], parts[1], parts);
	free_split(parts);
}
