/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:59 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/12 17:41:05 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv)
{
	t_mother	newgame;
	int			fd;

	ft_bzero(&newgame, sizeof(t_mother));
	valid_input_check(argc, argv, &newgame.map);
	newgame.map.grid = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		put_error("Failed to open file.");
	parse(&newgame.map, fd);
	if (newgame.map.textures_parsed != 5)
		put_error("Invalid amount of textures provided.");
	if (newgame.map.grid_parsed == 0)
		put_error("No map found.");
	check_valid_grid(newgame.map.grid);
	rotate_grid(&newgame.map);
	init_sprites(&newgame.map);
	initialize(&newgame.player, &newgame.ray, newgame.map.grid);
	flood_fill(&newgame.map, &newgame.player);
	draw(&newgame, &newgame.mlx, &newgame.mlx2);
	return (0);
}

int	close_window(t_mother *game)
{
	mlx_destroy_image(game->mlx.mlx, game->mlx.img);
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	free_stuff(&game->map);
	exit(0);
	return (0);
}
