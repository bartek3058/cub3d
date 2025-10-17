/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:34:00 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/17 10:33:30 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_blank_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\r');
}

int	parse_single_color_component(t_color_ctx *ctx, char *component)
{
	int	i;

	if (!component)
	{
		free_split(ctx->lines);
		free_split(ctx->parts);
		free_split(ctx->rgb);
		free_myconfig(&ctx->game->config);
		free_map_grid(ctx->game);
		exit_error("Invalid color: missing R,G or B value");
	}
	i = 0;
	while (component[i] && is_blank_char(component[i]))
		i++;
	if (!component[i])
	{
		free_split(ctx->lines);
		free_split(ctx->parts);
		free_split(ctx->rgb);
		free_myconfig(&ctx->game->config);
		free_map_grid(ctx->game);
		exit_error("Invalid color: missing R,G or B value");
	}
	return (ft_atoi(component));
}

void	exit_error(const char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, "Error\n", 6);
	write(2, msg, len);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
