/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:02:50 by brogalsk          #+#    #+#             */
/*   Updated: 2025/10/16 18:02:54 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
