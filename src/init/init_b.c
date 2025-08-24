#include "../../include/cub3d.h"

void    init_myconfig(t_mygame *game)
{
    game->config.tex_no = NULL;
    game->config.tex_so = NULL;
    game->config.tex_we = NULL;
    game->config.tex_ea = NULL;
    game->config.floor_color = -1; // -1 oznacza brak koloru
    game->config.ceil_color = -1;
}