#include "include/cub3d.h"

char *test_map[10] = {
    "1111111111",
    "1000000001",
    "1000000001",
    "1000000001",
    "1000000001",
    "1000000001",
    "1000000001",
    "1000000001",
    "1000000N01",
    "1111111111"
};

void allocate_map_grid(t_mygame *game)
{
    game->map.grid = malloc(sizeof(char *) * game->map.height);
    for (int y = 0; y < game->map.height; y++)
    {
        game->map.grid[y] = strdup(test_map[y]);
    }
}

int   game_loop(void *param)
{
    t_mygame *game = (t_mygame *)param;
    
    // Clear image buffer (fill with black or background color)
    int img_size = game->map.width * 20 * game->map.height * 20 * (game->img.bpp / 8);
    memset(game->img.addr, 0, img_size);
    if (game->key_w) game->player.y -= game->player.MOVE_SPEED;
    if (game->key_s) game->player.y += game->player.MOVE_SPEED;
    if (game->key_a) game->player.x -= game->player.MOVE_SPEED;
    if (game->key_d) game->player.x += game->player.MOVE_SPEED;
    printf("Player pos: %f %f\n", game->player.x, game->player.y);
    draw_2d_map(game); //Rysuje mapę 2D do bufora obrazu
    draw_player(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0); // Aktualizuje okno
    return (0);
}

static void none(int argc, char **argv) //funkcja do ignorowania warningów o nieużywanych zmiennych
{
    (void)argc;
    (void)argv;
}

int main (int argc, char **argv)
{
    t_mygame game;

    // FOR TESTING PURPOSES
    // For testing: set up a simple 10x10 map
    game.map.grid = test_map;
    game.map.width = 10;
    game.map.height = 10;


    // Optionally set player position manually if needed
    // game.player.x = 7.5;
    // game.player.y = 8.5;
    // game.player.dir_x = 0;
    // game.player.dir_y = -1;
    allocate_map_grid(&game);
    init_player_from_map(&game);
    none(argc, argv);
    //END FOR TESTING PURPOSES

    //check_map_name(argc, argv);
    //parser(argv, &game);

    
    if (!init_window(&game))
    {
        //cleanup_map(&game);     // trzeba będzie dopisać
        cleanup_display(&game);
        exit(EXIT_FAILURE);
    }
    game.img.img = mlx_new_image(game.mlx, 500, 500);
    game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_len, &game.img.endian);
    
    //mlx_pixel_put(game.mlx, game.win, 250, 250, 0xFFFFFF);
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);    // Key press
    mlx_hook(game.win, 3, 1L<<1, key_release, &game);  // Key release
    mlx_hook(game.win, 17, 0, close_hook, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
	cleanup_all(&game);
	exit(EXIT_SUCCESS);
}