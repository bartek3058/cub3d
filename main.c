#include "include/cub3d.h"

int main (int argc, char **argv)
{
    t_mygame game;

    check_map_name(argc, argv);
    parser(argv, &game);
    if (!init_window(&game))
    {
        //cleanup_map(&game);     // trzeba będzie dopisać
        cleanup_display(&game);
        exit(EXIT_FAILURE);
    }
    mlx_pixel_put(game.mlx, game.win, 250, 250, 0xFFFFFF);
    mlx_hook(game.win, 17, 0, close_hook, &game);
	mlx_key_hook(game.win, keys_hook, &game);
	//mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
	cleanup_all(&game);
	exit(EXIT_SUCCESS);
}