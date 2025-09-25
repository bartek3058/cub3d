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

static int	parse_color(char *str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;
	
	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	color = (r << 16) | (g << 8) | b;
	free_split(rgb);
	return (color);
}

static void	save_config_line(t_mygame *game, char *line)
{
	char **parts;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1])
		return ;
	if (!ft_strcmp(parts[0], "NO"))
		game->config.tex_no = ft_strdup(parts[1]);
	else if (!ft_strcmp(parts[0], "SO"))
		game->config.tex_so = ft_strdup(parts[1]);
	else if (!ft_strcmp(parts[0], "WE"))
		game->config.tex_we = ft_strdup(parts[1]);
	else if (!ft_strcmp(parts[0], "EA"))
		game->config.tex_ea = ft_strdup(parts[1]);
	else if (!ft_strcmp(parts[0], "F"))
		game->config.floor_color = parse_color(parts[1]);
	else if (!ft_strcmp(parts[0], "C"))
		game->config.ceil_color = parse_color(parts[1]);
	free_split(parts);
	// printf("kolor sufitu: %d\n", game->config.ceil_color);
	// printf("kolor podłogi: %d\n", game->config.floor_color);
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

