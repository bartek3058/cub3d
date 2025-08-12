#include "include/cub3d.h"

int main (int argc, char **argv)
{
    t_game game;

    check_map_name(argc, argv);
    window_size(game, argv);
    configuration_map_checker(game, argv);
}