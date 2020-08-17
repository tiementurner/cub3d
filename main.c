/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:59 by tblanker      #+#    #+#                 */
/*   Updated: 2020/08/16 15:36:08 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv)
{
	mother newgame;
	int fd;

	fd = argc;
	newgame.map.grid = NULL;
	fd = open(argv[1], O_RDONLY);
	parse(&newgame.map, fd);
	initialize(&newgame.player, &newgame.ray, &newgame.map.grid);
	draw(&newgame);
	return (0);
}

int	print_keycode(int keycode)
{
	printf("keycode: %d\n", keycode);
	return (0);
}

int	close_window(int keycode, data *win)
{
	if (keycode == 65307)
		mlx_destroy_window(win->mlx, win->win);
	return (0);
}

int	move(int keycode, data *new_game)
{
	double	rot_speed;
	double	old_dir_X;
	double	old_plane_X;

	rot_speed = 0.1;
	if (keycode == 13)
		move_up(new_game);
	if (keycode == 1)
		move_down(new_game);
	if (keycode == 2)
		move_right(new_game);
	if (keycode == 0)
		move_left(new_game);
	if (keycode == 124)
	{
		old_dir_X = new_game->dir_X;
		new_game->dir_X = new_game->dir_X * cos(-rot_speed) - new_game->dir_Y * sin(-rot_speed);
		new_game->dir_Y = old_dir_X * sin(-rot_speed) + new_game->dir_Y * cos(-rot_speed);
		old_plane_X = new_game->plane_X;
		new_game->plane_X = new_game->plane_X * cos(-rot_speed) - new_game->plane_Y * sin(-rot_speed);
		new_game->plane_Y = old_plane_X * sin(-rot_speed) + new_game->plane_Y * cos(-rot_speed);
	}
		if (keycode == 123)
	{
		old_dir_X = new_game->dir_X;
		new_game->dir_X = new_game->dir_X * cos(rot_speed) - new_game->dir_Y * sin(rot_speed);
		new_game->dir_Y = old_dir_X * sin(rot_speed) + new_game->dir_Y * cos(rot_speed);
		old_plane_X = new_game->plane_X;
		new_game->plane_X = new_game->plane_X * cos(rot_speed) - new_game->plane_Y * sin(rot_speed);
		new_game->plane_Y = old_plane_X * sin(rot_speed) + new_game->plane_Y * cos(rot_speed);
	}
	return (0);
}
