#include "../../include/cub3d.h"

#define TITLE_SIZE 10

void   draw_square(t_myimg *img, int x, int y, int color, int size)
{
    int     i;
    int     j;
    int     px;
    int     py;
    char    *dst;

    i = 0;
    while (i < size - 1)
    {
        j = 0;
        while (j < size - 1)
        {
            px = x * size + j;
            py = y * size + i;
            dst = img->addr + (py * img->line_len + px * (img->bpp / 8));
            *(unsigned int*)dst = color;
            j++;
        }
        i++;
    }
}

void   draw_player(t_mygame *game)
{
    //int x;
    //int y;
    //int color;

    int px = (int)(game->player.x * TITLE_SIZE - 2);
    int py = (int)(game->player.y * TITLE_SIZE - 2);
    //color = 0xFF0000; // czerwony dla gracza
    //draw_square(&game->img, x, y, color, 4);
    // for testing
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            int x = px + j;
            int y = py + i;
            if (x >= 0 && x < game->map.width * TITLE_SIZE && y >= 0 && y < game->map.height * TITLE_SIZE) {
                char *dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
                *(unsigned int*)dst = 0xFF0000;
            }
        }
    // end testing
}

void   draw_2d_map(t_mygame *game)
{
    int     x;
    int     y;
    char    cell;
    int     color;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            cell = game->map.grid[y][x];
            if (cell == '1')
                color = 0xFFFFFF; // biały dla ścian
            else if (cell == '0')
                color = 0xCCCCCC; // szary dla przestrzeni
            else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
                color = 0xCCCCCC;
            else
                color = 0xFF00FF; // magenta dla innych znaków (błąd)
            draw_square(&game->img, x, y, color, TITLE_SIZE);
            x++;
        }
        y++;
    }
}

// void   draw_all(t_mygame *game)
// {
//     draw_2d_map(game);
//     draw_player(game);
// }