#include "../include/cub3D.h"

void	cleanup_display(t_mygame *game)
{
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
	// Cleanup other resources (textures, images, etc.)
    //cleanup_images(game);
    //cleanup_map(game);
    //cleanup_textures(game);
    //cleanup_player(game);
}