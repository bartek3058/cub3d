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
	return (max - 1);
}


void	init_map(t_mygame *game, char **lines, int a)
{
	int i;

	i = 0;
	game->map.height = 0;
	while (lines[a + game->map.height] && !is_blank(lines[a + game->map.height]))
		game->map.height++;
	game->map.width = get_map_width(&lines[a]);
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return ;
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_strdup(lines[a]);
		a++;
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