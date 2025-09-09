#include "../../include/cub3d.h"

static int	is_move_valid(t_mygame *game, int new_x_pos, int new_y_pos)
{
	if (new_x_pos < 0 || new_y_pos < 0
		|| new_x_pos >= game->map.width || new_y_pos >= game->map.height)
		return (0);
	if (new_x_pos == game->player.x && new_y_pos == game->player.y)
		return (0);
	if (game->map.grid[new_y_pos][new_x_pos] == '1')
		return (0);
	return (1);
}

void	update_player_pos(t_mygame *game, int new_x_pos, int new_y_pos)
{
	game->player.x = new_x_pos;
	game->player.y = new_y_pos;
    draw_player(game);
}

void	move_player(t_mygame *game, int new_x_pos, int new_y_pos)
{
	if (!is_move_valid(game, new_x_pos, new_y_pos))
		return ;
	update_player_pos(game, new_x_pos, new_y_pos);
}