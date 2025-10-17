/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:33:09 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/17 10:33:10 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_color(t_color_ctx *ctx, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		if (r < 0 || r > 255)
			printf("Invalid color: %d\n", r);
		else if (g < 0 || g > 255)
			printf("Invalid color: %d\n", g);
		else
			printf("Invalid color: %d\n", b);
		free_split(ctx->rgb);
		free_split(ctx->lines);
		free_split(ctx->parts);
		free_map_grid(ctx->game);
		free_myconfig(&ctx->game->config);
		exit(EXIT_FAILURE);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_blank(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r' && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
