/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:49:13 by tszymans          #+#    #+#             */
/*   Updated: 2025/09/16 09:49:13 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

char *test_map[10] = {
	"1111111111",
	"1000000001",
	"1000000001",
	"1001100001",
	"1001100001",
	"1000000001",
	"1000000001",
	"10N0000001",
	"1000000001",
	"1111111111"};

void allocate_map_grid(t_mygame *game)
{
	game->map.grid = malloc(sizeof(char *) * game->map.height);
	for (int y = 0; y < game->map.height; y++)
	{
		game->map.grid[y] = strdup(test_map[y]);
	}
}

int game_loop(t_mygame *game)
{
	int img_size;

	// Update player position based on keys pressed
	if (game->key_w)
		move_player(game, game->player.x,
			game->player.y - game->player.move_speed);
	if (game->key_s)
		move_player(game, game->player.x,
			game->player.y + game->player.move_speed);
	if (game->key_a)
		move_player(game, game->player.x - game->player.move_speed,
			game->player.y);
	if (game->key_d)
		move_player(game, game->player.x + game->player.move_speed,
			game->player.y);
	if (game->key_left_arrow)
		rotate_player(game, -game->player.rot_speed);
	if (game->key_right_arrow)
		rotate_player(game, game->player.rot_speed);
	img_size = game->img.line_len * 768;
	memset(game->img.addr, 0, img_size);
	draw_2d_map(game); // Rysuje mapę 2D do bufora obrazu
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

static void	none(int argc, char **argv) // ignorowanie warningów o nieużywanych zmiennych
{
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv)
{
	t_mygame	game;

	// Reset keys pressed state
	game.key_w = 0;
	game.key_s = 0;
	game.key_a = 0;
	game.key_d = 0;
	game.key_left_arrow = 0;
	game.key_right_arrow = 0;
	game.key_esc = 0;

	// FOR TESTING PURPOSES
	// For testing: set up a simple 10x10 map
	game.map.grid = test_map;
	game.map.width = 10;
	game.map.height = 10;

	allocate_map_grid(&game);
	game.map.tile_size = 10; // Each tile is 10x10 pixels
	init_player_from_map(&game);
	none(argc, argv);
	// END FOR TESTING PURPOSES

	// check_map_name(argc, argv);
	// parser(argv, &game);

	if (!init_window(&game))
	{
		// cleanup_map(&game);     // trzeba będzie dopisać
		cleanup_display(&game);
		exit(EXIT_FAILURE);
	}
	game.img.img = mlx_new_image(game.mlx, 1024, 768);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_len, &game.img.endian);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_hook, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_all(&game);
	exit(EXIT_SUCCESS);
}
