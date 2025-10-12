#include "../../include/cub3d.h"

// static void    cleanup_textures(t_mygame *game)
// {
//     free(game->config.tex_no);
//     free(game->config.tex_so);
//     free(game->config.tex_we);
//     free(game->config.tex_ea);
//     game->config.tex_no = NULL;
//     game->config.tex_so = NULL;
//     game->config.tex_we = NULL;
//     game->config.tex_ea = NULL;
// }

static void	cleanup_map(t_mygame *game)
{
	int i;

	if (!game->map.grid)
		return ;
	i = 0;
	while (i < game->map.height)
	{
		free(game->map.grid[i]);
		i++;
	}
	// free_split(game->map.grid);
	free(game->map.grid); // <--- ADD THIS LINE
	game->map.grid = NULL;
}

void	cleanup_display(t_mygame *game)
{
	if (game->img.img)
    {
        mlx_destroy_image(game->mlx, game->img. img);
        game->img.img = NULL;
    }
	free_myconfig(&game->config);
	free_map_grid(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	cleanup_all(t_mygame *game)
{
	cleanup_display(game);
    cleanup_map(game);
}
