#include "../../include/cub3d.h"

static void	check_xpm_extension(char *filename)
{
	char	*trimmed;
	int		len;

	trimmed = ft_strtrim(filename, " \t\n\r");
	if (!trimmed)
		exit_error("malloc failed");
	len = ft_strlen(trimmed);
	if (len < 4 || ft_strcmp(trimmed + len - 4, ".xpm") != 0)
	{
		free(trimmed);
		exit_error("Error: texture file must have .xpm extension");
	}

	free(trimmed);
}

void	save_texture(t_myconfig *cfg, char *key, char *value)
{
	if (!ft_strcmp(key, "NO"))
	{
		if (cfg->tex_no != NULL)
			exit_error("duplicate NO texture");
		check_xpm_extension(value);
		cfg->tex_no = ft_strdup(value);
	}
	else if (!ft_strcmp(key, "SO"))
	{
		if (cfg->tex_so != NULL)
			exit_error("duplicate SO texture");
		check_xpm_extension(value);
		cfg->tex_so = ft_strdup(value);
	}
	else if (!ft_strcmp(key, "WE"))
	{
		if (cfg->tex_we != NULL)
			exit_error("duplicate WE texture");
		check_xpm_extension(value);
		cfg->tex_we = ft_strdup(value);
	}
	else if (!ft_strcmp(key, "EA"))
	{
		if (cfg->tex_ea != NULL)
			exit_error("duplicate EA texture");
		check_xpm_extension(value);
		cfg->tex_ea = ft_strdup(value);
	}
}


void	save_color(t_myconfig *cfg, char *key, char *value)
{
	if (!ft_strcmp(key, "F"))
	{
		if (cfg->floor_color != -1)
			exit_error("duplicate floor color");
		cfg->floor_color = parse_color(value);
	}
	else if (!ft_strcmp(key, "C"))
	{
		if (cfg->ceil_color != -1)
			exit_error("duplicate ceiling color");
		cfg->ceil_color = parse_color(value);
	}
}

void	check_color(int r, int g, int b)
{
	if (r < 0 || r > 255)
	{
		printf("Invalid color: %d\n", r);
		exit(EXIT_FAILURE);
	}
	if (g < 0 || g > 255)
	{
		printf("Invalid color: %d\n", g);
		exit(EXIT_FAILURE);
	}
	if (b < 0 || b > 255)
	{
		printf("Invalid color: %d\n", b);
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
