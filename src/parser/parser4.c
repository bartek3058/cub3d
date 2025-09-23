#include "../../include/cub3d.h"

static void    my_mlx_pixel_put(t_myimg *img, int x, int y, int color)
{
    char    *dst;


    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}


void    draw_background(t_mygame *game)
{
    int x, y;

    game->mlx = mlx_init();
    if (!game->mlx)
    {
        perror("mlx_init failed");
        exit(1);
    }
	init_image(game, game->map.width, game->map.height);
    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (y < game->map.height / 2)
                my_mlx_pixel_put(&game->img, x, y, game->config.ceil_color);
            else
                my_mlx_pixel_put(&game->img, x, y, game->config.floor_color);
            x++;
        }
        y++;
    }
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