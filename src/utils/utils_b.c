/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:29:28 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/17 10:32:31 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	check_xpm_extension(t_mygame *game, char *filename,
		char **lines, char **parts)
{
	char	*trimmed;
	int		len;

	trimmed = ft_strtrim(filename, " \t\n\r");
	if (!trimmed)
		exit_error("malloc failed");
	len = ft_strlen(trimmed);
	if (len < 4 || ft_strcmp(trimmed + len - 4, ".xpm") != 0)
	{
		free_split(lines);
		free_split(parts);
		free_myconfig(&game->config);
		free_map_grid(game);
		free(trimmed);
		exit_error("Error: texture file must have .xpm extension");
	}
	free(trimmed);
}

static void	exit_texture_error(t_tex_ctx *tctx, char *msg)
{
	free_split(tctx->ctx->lines);
	free_split(tctx->parts);
	free_map_grid(tctx->ctx->game);
	free_myconfig(&tctx->ctx->game->config);
	exit_error(msg);
}

static void	set_texture(t_tex_ctx *tctx, char **tex_slot, char *value,
		char *name)
{
	if (*tex_slot != NULL)
		exit_texture_error(tctx, name);
	check_xpm_extension(tctx->ctx->game, value, tctx->ctx->lines, tctx->parts);
	*tex_slot = ft_strdup(value);
}

void	save_texture(t_parse_ctx *ctx, char *key, char *value, char **parts)
{
	t_tex_ctx	tctx;

	tctx.ctx = ctx;
	tctx.parts = parts;
	if (!ft_strcmp(key, "NO"))
		set_texture(&tctx, &ctx->game->config.tex_no, value,
			"duplicate NO texture");
	else if (!ft_strcmp(key, "SO"))
		set_texture(&tctx, &ctx->game->config.tex_so, value,
			"duplicate SO texture");
	else if (!ft_strcmp(key, "WE"))
		set_texture(&tctx, &ctx->game->config.tex_we, value,
			"duplicate WE texture");
	else if (!ft_strcmp(key, "EA"))
		set_texture(&tctx, &ctx->game->config.tex_ea, value,
			"duplicate EA texture");
}

void	save_color(t_parse_ctx *ctx, char *key, char *value, char **parts)
{
	if (!ft_strcmp(key, "F"))
	{
		if (ctx->game->config.floor_color != -1)
			exit_error("duplicate floor color");
		ctx->game->config.floor_color = parse_color(value,
				ctx->lines, parts, ctx->game);
	}
	else if (!ft_strcmp(key, "C"))
	{
		if (ctx->game->config.ceil_color != -1)
			exit_error("duplicate ceiling color");
		ctx->game->config.ceil_color = parse_color(value, ctx->lines,
				parts, ctx->game);
	}
}
