#include "../../include/cub3d.h"

void	check_trailing_lines(char **lines, int map_end_index)
{
	int i = map_end_index + 1;

	while (lines[i])
	{
		if (!is_blank(lines[i]))
			exit_error("Invalid character(s) after map");
		i++;
	}
}

static void	check_textures(t_mygame *game)
{
	if (game->config.tex_no == NULL)
	{
		printf("Missing NO path\n");
		exit(EXIT_FAILURE);
	}
	if (game->config.tex_so == NULL)
	{
		printf("Missing SO path\n");
		exit(EXIT_FAILURE);
	}
	if (game->config.tex_we == NULL)
	{
		printf("Missing WE path\n");
		exit(EXIT_FAILURE);
	}
	if (game->config.tex_ea == NULL)
	{
		printf("Missing EA path\n");
		exit(EXIT_FAILURE);
	}
}

static void	check_colors(t_mygame *game)
{
	if (game->config.floor_color == -1)
	{
		printf("Missing floor color\n");
		exit(EXIT_FAILURE);
	}
	if (game->config.ceil_color == -1)
	{
		printf("Missing ceil color\n");
		exit(EXIT_FAILURE);
	}
}

void	check_config(t_mygame *game)
{
	check_textures(game);
	check_colors(game);
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