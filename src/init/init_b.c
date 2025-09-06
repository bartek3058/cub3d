#include "../../include/cub3d.h"

static int	get_map_width(char **lines)
{
	int i;
	int len;
	int max;

	i = 0;
	max = 0;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}


void	init_map(t_mygame *game, char **lines)
{
	int	i;

	game->map.height = 0;
	while (lines[game->map.height])
		game->map.height++;
	game->map.width = get_map_width(lines);
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return ;
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_strdup(lines[i]);
		i++;
	}
	game->map.grid[i] = NULL;
}


void    init_myconfig(t_mygame *game)
{
    game->config.tex_no = NULL;
    game->config.tex_so = NULL;
    game->config.tex_we = NULL;
    game->config.tex_ea = NULL;
    game->config.floor_color = -1; // -1 oznacza brak koloru
    game->config.ceil_color = -1;
}