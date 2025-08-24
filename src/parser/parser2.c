#include "../../include/cub3d.h"

void	parse_texture(char **tokens, char **dest, char **lines)
{
	if (*dest != NULL)
	{
		write(2, "Error\nDuplicate texture definition\n", 35);
		free_split(lines);
		exit(EXIT_FAILURE);
	}
	if (!tokens[1])
	{
		write(2, "Error\nMissing texture path\n", 28);
		free_split(lines);
		exit(EXIT_FAILURE);
	}
	*dest = strdup(tokens[1]);
	if (!*dest)
	{
		perror("Error\nMalloc failed");
		free_split(lines);
		exit(EXIT_FAILURE);
	}
}