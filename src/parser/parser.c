#include "../../include/cub3d.h"

void    parser(char **argv, t_mygame *game)
{
    char **lines;
    int map_start;

    lines = load_map(argv[1]);
    map_start = parse_config(lines, game);
    check_config(game);
    init_map(game, lines, map_start);
    parse_map(game);
    check_trailing_lines(lines, map_start + game->map.height - 1);
    // check_after_map(game, lines);
    free_split(lines);
    // draw_background(game);
    
    // printf("wysokość %d\n",game->map.height);
    // printf("szerokosc %d\n",game->map.width);
    // int i;
    // i = 0;
    // while (i < game->map.height)
    // {
    //     printf("%s\n", game->map.grid[i]);
    //     i++;
    // }
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
            exit_error("Error: multiple player positions");
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

static void flood_check(t_mygame *game, int y, int x)
{
    char **grid = game->map.grid;

    // wyjście poza tablicę → mapa otwarta
    if (y < 0 || y >= game->map.height || x < 0 || x >= (int)ft_strlen(grid[y]))
        exit_error("Error: map not closed (edge)");

    if (grid[y][x] == ' ')
        exit_error("Error: map not closed (space hole)");

    // ściana lub odwiedzone
    if (grid[y][x] == '1' || grid[y][x] == 'V')
        return;

    // oznacz odwiedzone
    grid[y][x] = 'V';

    // rekurencja w 4 strony
    flood_check(game, y - 1, x);
    flood_check(game, y + 1, x);
    flood_check(game, y, x - 1);
    flood_check(game, y, x + 1);
}

void validate_map_closed(t_mygame *game)
{
    int y = 0;
    int x;

    while (y < game->map.height)
    {
        x = 0;
        while (x < (int)ft_strlen(game->map.grid[y]))
        {
            if (game->map.grid[y][x] == '0' || is_player_char(game->map.grid[y][x]))
                flood_check(game, y, x);
            x++;
        }
        y++;
    }

    // przywracamy 'V' na '0'
    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < (int)ft_strlen(game->map.grid[y]))
        {
            if (game->map.grid[y][x] == 'V')
                game->map.grid[y][x] = '0';
            x++;
        }
        y++;
    }
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
        exit_error("Error: no player position found");
        return 1;
    }
    validate_map_closed(game);
    return 0;
}

