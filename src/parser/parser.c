#include "../../include/cub3d.h"

void    parser(char **argv, t_mygame *game)
{
    char **lines;
    int map_start;

    lines = load_map(argv[1]);
    map_start = parse_config(lines, game);
    init_map(game, lines, map_start);
    parse_map(game);
    // printf("wysokość %d\n",game->map.height);
    // printf("szerokosc %d\n",game->map.width);
    // int i;
    // i = 0;
    // while (i < game->map.height)
    // {
    //     printf("%s\n", game->map.grid[i]);
    //     i++;
    // }
    free_split(lines);
}
static int is_player_char(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    return (0);
}

static int handle_tile(t_mygame *game, int i, int j, int *player_found)
{
    char c;

    c = game->map.grid[i][j];
    if (c == '1' || c == '0' || c == ' ')
        return 0;
    if (is_player_char(c))
    {
        if (*player_found == 1)
        {
            fprintf(stderr, "Error: multiple player positions\n");
            return 1;
        }
        *player_found = 1;
        game->player.x = j + 0.5;
        game->player.y = i + 0.5;
        set_player_direction(&game->player, c);
        game->map.grid[i][j] = '0';
        return 0;
    }
    // fprintf(stderr, "Error: invalid char '%c' at (%d,%d)\n", c, i, j);
    return 1;
}

int parse_map(t_mygame *game)
{
    int i;
    int j;
    int err;
    int player_found;

    i = 0;
    player_found = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            err = handle_tile(game, i, j, &player_found);
            if (err == 1)
                return 1;
            j++;
        }
        i++;
    }
    if (player_found == 0)
    {
        fprintf(stderr, "Error: no player position found\n");
        return 1;
    }
    return 0;
}

