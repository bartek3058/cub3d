#include "../../include/cub3d.h"

void    check_map_name(int argc, char **argv)
{
    size_t len;

    if (argc != 2)
    {
        printf("Error\nThere is no map argument\n");
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
    if (ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])) == NULL)
	{
		printf("Error\nmap should be .cub\n");
		exit(EXIT_FAILURE);
	}
}
static  char    *read_file(int fd)
{
    char    buf[1025];
    char    *content;
    char    *tmp;
    int     bytes;

    content = malloc(1);
    if (!content)
        return (NULL);
    content[0] = '\0';
    while ((bytes = read(fd, buf, 1024)) > 0)
    {
        buf[bytes] = '\0';
        tmp = ft_strjoin(content, buf);
        free(content);
        content = tmp;
    }
    return (content);
}
char    **load_map(char *filename)
{
    int     fd;
    char    *file_content;
    char    **lines;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error\nInvalid map");
        exit(EXIT_FAILURE);
    }
    file_content = read_file(fd);
    close(fd);
    if (!file_content || file_content[0] == '\0')
    {
        free(file_content);
        write(2, "Error\nEmpty file\n", 17);
        exit(EXIT_FAILURE);
    }
    lines = ft_split(file_content, '\n');
    free(file_content);
    return (lines);
}
