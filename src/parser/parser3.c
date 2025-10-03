#include "../../include/cub3d.h"

static int starts_with_token(const char *s, const char *tok)
{
	int i;
	int j;

	if (!s || !tok)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	j = 0;
	while (tok[j] && s[i + j] && s[i + j] == tok[j])
		j++;
	if (tok[j] != '\0')
		return (0);
	if (s[i + j] == ' ' || s[i + j] == '\t' || s[i + j] == '\0')
		return (1);
	return (0);
}

static int is_config_line(char *line)
{
	if (!line || is_blank(line))
		return (0);
	if (starts_with_token(line, "NO") || starts_with_token(line, "SO") ||
	    starts_with_token(line, "WE") || starts_with_token(line, "EA") ||
	    starts_with_token(line, "F")  || starts_with_token(line, "C"))
		return (1);
	return (0);
}

int	parse_color(char *str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;
	
	rgb = ft_split(str, ',');
	printf ("%s", rgb[2]);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2]
		|| !rgb[0][1] || !rgb[1][1] || !rgb[2][1])
			exit_error("Invalid color: missing R,G or B value");
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	check_color(r,g,b);
	color = (r << 16) | (g << 8) | b;
	free_split(rgb);
	return (color);
}


static void	save_config_line(t_mygame *game, char *line)
{
	char **parts;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1])
	{
		exit_error("invalid config line");
	}
	save_texture(&game->config, parts[0], parts[1]);
	save_color(&game->config, parts[0], parts[1]);
	free_split(parts);
}

int parse_config(char **lines, t_mygame *game)
{
	int i;

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
			save_config_line(game, lines[i]);
			i++;
			continue ;
		}
		break ;
	}
	return (i); /* index pierwszego wiersza mapy */
}

