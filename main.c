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

int game_loop(t_mygame *game)
{
	int img_size;

	// Update player position based on keys pressed
	update_player_controls(game);

	img_size = game->img.line_len * game->scr_height;
	memset(game->img.addr, 0, img_size);
	draw_background(game);
	raycaster(&game->ray, game); // Rysuje widok 3D do bufora obrazu
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

	init_game(&game);
	none(argc, argv);
	check_map_name(argc, argv);
	parser(argv, &game);
	if (!init_window(&game))
	{
		// cleanup_map(&game);     // trzeba będzie dopisać
		// cleanup_display(&game);
		cleanup_all(&game);
		exit(EXIT_FAILURE);
	}
	//init_player_from_map(&game);
	init_player(&game);
	game.img.img = mlx_new_image(game.mlx, game.scr_width, game.scr_height);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_len, &game.img.endian);
	// game.config.ceil_color = 0xFF0000;
	// game.config.floor_color = 0xFF0000;
	// draw_background(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_hook(game.win, 17, 0, close_hook, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_all(&game);
	exit(EXIT_SUCCESS);
}
