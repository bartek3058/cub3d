#include "../../include/cub3d.h"

#define TITLE_SIZE 20

void   draw_square(t_myimg *img, int x, int y, int color)
{
    int     i;
    int     j;
    int     px;
    int     py;
    char    *dst;

    i = 0;
    while (i < TITLE_SIZE - 1)
    {
        j = 0;
        while (j < TITLE_SIZE - 1)
        {
            px = x * TITLE_SIZE + j;
            py = y * TITLE_SIZE + i;
            dst = img->addr + (py * img->line_len + px * (img->bpp / 8));
            *(unsigned int*)dst = color;
            j++;
        }
        i++;
    }
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
                color = 0xFF0000; // czerwony dla gracza
            else
                color = 0xFF00FF; // magenta dla innych znaków (błąd)
            draw_square(&game->img, x, y, color);
            x++;
        }
        y++;
    }
}