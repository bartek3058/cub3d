#include "../../include/cub3d.h"

static void    my_mlx_pixel_put(t_myimg *img, int x, int y, int color)
{
    char    *dst;


    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}


void draw_background(t_mygame *game)
{
    int x, y;

	printf("kolor sufitu: %d\n", game->config.ceil_color);
	printf("kolor podłogi: %d\n", game->config.floor_color);
    y = 0;
    while (y < game->scr_height)
    {
        x = 0;
        while (x < game->scr_width)
        {
            if (y < game->scr_height / 2)
                my_mlx_pixel_put(&game->img, x, y, game->config.ceil_color);
			else
                my_mlx_pixel_put(&game->img, x, y, game->config.floor_color);
            x++;
        }
        y++;
    }
}