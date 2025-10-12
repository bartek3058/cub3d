#include "../../include/cub3d.h"

static void	check_xpm_extension(t_mygame *game, char *filename, char **lines, char **parts)
{
	char	*trimmed;
	int		len;

	trimmed = ft_strtrim(filename, " \t\n\r");
	if (!trimmed)
		exit_error("malloc failed");
	len = ft_strlen(trimmed);
	if (len < 4 || ft_strcmp(trimmed + len - 4, ".xpm") != 0)
	{
		free_split(lines);
		free_split(parts);
		free_myconfig(&game->config);
		free_map_grid(game);
		free(trimmed);
		exit_error("Error: texture file must have .xpm extension");
	}

	free(trimmed);
}

void	save_texture(t_mygame *game, char *key, char *value, char **lines, char **parts)
{
	if (!ft_strcmp(key, "NO"))
	{
		if (game->config.tex_no != NULL)
		{
			free_split(lines);
			free_split(parts);
			free_map_grid(game);
			free_myconfig(&game->config);
			exit_error("duplicate NO texture");
		}
		check_xpm_extension(game, value, lines, parts);
		game->config.tex_no = ft_strdup(value);
	}
	else if (!ft_strcmp(key, "SO"))
	{
		if (game->config.tex_so != NULL)
		{
			free_split(lines);
			free_split(parts);
			free_map_grid(game);
			free_myconfig(&game->config);
			exit_error("duplicate SO texture");
		}
		check_xpm_extension(game, value, lines, parts);
		game->config.tex_so = ft_strdup(value);
	}
	else if (!ft_strcmp(key, "WE"))
	{
		if (game->config.tex_we != NULL)
		{
			free_split(lines);
			free_split(parts);
			free_map_grid(game);
			free_myconfig(&game->config);
			exit_error("duplicate WE texture");
		}
		check_xpm_extension(game, value, lines, parts);
		game->config.tex_we = ft_strdup(value);
	}
	else if (!ft_strcmp(key, "EA"))
	{
		if (game->config.tex_ea != NULL)
		{
			free_split(lines);
			free_split(parts);
			free_map_grid(game);
			free_myconfig(&game->config);
			exit_error("duplicate EA texture");
		}
		check_xpm_extension(game, value, lines, parts);
		game->config.tex_ea = ft_strdup(value);
	}
}


void	save_color(t_mygame *game, char *key, char *value, char **lines, char **parts)
{
	if (!ft_strcmp(key, "F"))
	{
		if (game->config.floor_color != -1)
			exit_error("duplicate floor color");
		game->config.floor_color = parse_color(value, lines, parts, game);
	}
	else if (!ft_strcmp(key, "C"))
	{
		if (game->config.ceil_color != -1)
			exit_error("duplicate ceiling color");
		game->config.ceil_color = parse_color(value, lines, parts, game);
	}
}

void	check_color(int r, int g, int b, char **lines, char **rgb, char **parts, t_mygame *game)
{
	if (r < 0 || r > 255)
	{
		printf("Invalid color: %d\n", r);
		free_split(rgb);
		free_split(lines);
		free_split(parts);
		free_map_grid(game);
		free_myconfig(&game->config);
		exit(EXIT_FAILURE);
	}
	if (g < 0 || g > 255)
	{
		printf("Invalid color: %d\n", g);
		free_split(rgb);
		free_split(lines);
		free_split(parts);
		free_map_grid(game);
		free_myconfig(&game->config);
		exit(EXIT_FAILURE);
	}
	if (b < 0 || b > 255)
	{
		printf("Invalid color: %d\n", b);
		free_split(rgb);
		free_split(lines);
		free_split(parts);
		free_map_grid(game);
		free_myconfig(&game->config);
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

int is_blank(const char *s)
{
	int i;

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
