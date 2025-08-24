#include "../../include/cub3d.h"

static int	parse_rgb_component(char *s, char **lines)
{
	int	val;

	val = atoi(s);
	if (val < 0 || val > 255)
	{
		write(2, "Error\nRGB out of range\n", 24);
		free_split(lines);
		exit(EXIT_FAILURE);
	}
	return (val);
}

static int	rgb_to_int(char *s, char **lines)
{
	char	**split;
	int		r;
	int		g;
	int		b;
	int		color;

	split = ft_split(s, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		write(2, "Error\nInvalid RGB format\n", 26);
		free_split(lines);
		exit(EXIT_FAILURE);
	}
	r = parse_rgb_component(split[0], lines);
	g = parse_rgb_component(split[1], lines);
	b = parse_rgb_component(split[2], lines);
	color = (r << 16) | (g << 8) | b;
	free_split(split);
	return (color);
}

static void	parse_color(char **tokens, int *dest, char **lines)
{
	if (*dest != -1)
	{
		write(2, "Error\nDuplicate color definition\n", 33);
		free_split(lines);
		exit(EXIT_FAILURE);
	}
	if (!tokens[1])
	{
		write(2, "Error\nMissing color value\n", 27);
		free_split(lines);
		exit(EXIT_FAILURE);
	}
	*dest = rgb_to_int(tokens[1], lines);
}

static int	handle_tokens(char **tokens, t_mygame *game, char **lines)
{
	if (strcmp(tokens[0], "NO") == 0)
		parse_texture(tokens, &game->config.tex_no, lines);
	else if (strcmp(tokens[0], "SO") == 0)
		parse_texture(tokens, &game->config.tex_so, lines);
	else if (strcmp(tokens[0], "WE") == 0)
		parse_texture(tokens, &game->config.tex_we, lines);
	else if (strcmp(tokens[0], "EA") == 0)
		parse_texture(tokens, &game->config.tex_ea, lines);
	else if (strcmp(tokens[0], "F") == 0)
		parse_color(tokens, &game->config.floor_color, lines);
	else if (strcmp(tokens[0], "C") == 0)
		parse_color(tokens, &game->config.ceil_color, lines);
	else
		return (0);
	return (1);
}

void	parser(char **lines, t_mygame *game)
{
	int		i;
	char	**tokens;

	i = 0;
	init_myconfig(game);
	while (lines[i])
	{
		if (lines[i][0] == '\0')
		{
			i++;
			continue;
		}
		tokens = ft_split(lines[i], ' ');
		if (tokens && tokens[0])
		{
			if (!handle_tokens(tokens, game, lines))
			{
				free_split(tokens);
				break ;
			}
		}
		free_split(tokens);
		i++;
	}
}

