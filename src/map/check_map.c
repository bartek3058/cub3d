#include "../../include/cub3d.h"

// void    configuration_map_checker(t_game *game, char **argv);
// {
    
// }
void    check_map_name(int argc, char **argv)
{
    size_t len;
    char   *ext;

    if (argc != 2)
    {
        printf("Error\nThere is no map argument");
        exit (1);
    }
    if (!argv[1])
    {
        write(2, "Error\nNull filename\n", 20);
        exit(1);
    }
    len = ft_strlen(argv[1]);
    if (len < 4) // zabezpieczenie przed underflow
    {
        write(2, "Error\nWrong file extension\n", 27);
        exit(1);
    }
    ext = argv[1] + (len - 4);
    if (ft_strncmp(ext, ".cub", 4) != 0)
    {
        write(2, "Error\nWrong file extension\n", 27);
        exit(1);
    }
}
void    window_size(char **argv)
{
    int fd;

    fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nInvalid map_path/map\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])) == NULL)
	{
		printf("Error\nmap should be .cub\n");
		exit(EXIT_FAILURE);
	}
}