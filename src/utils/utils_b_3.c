#include "../../include/cub3d.h"

int	is_blank_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\r');
}

int	parse_single_color_component(char *component, char **lines, char **rgb, t_mygame *game, char **parts)
{
	int	i;

	if (!component)
	{
		free_split(lines);
		free_split(parts);
		free_split(rgb);
		free_myconfig(&game->config);
		free_map_grid(game);
		exit_error("Invalid color: missing R,G or B value");
	}
	i = 0;
	while (component[i] && is_blank_char(component[i]))
		i++;
	if (!component[i])
	{
		free_split(lines);
		free_split(parts);
		free_split(rgb);
		free_myconfig(&game->config);
		free_map_grid(game);
		exit_error("Invalid color: missing R,G or B value");
	}
	return (ft_atoi(component));
}


