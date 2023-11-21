/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhandling.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 16:49:43 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/12 17:38:39 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#ifdef __APPLE__
int		key_press_hook(int keycode, t_mother *new_game)
{
	printf("%d\n", keycode);
	if (keycode == 13)
		new_game->ray.walk_forward = 1;
	if (keycode == 1)
		new_game->ray.walk_backward = 1;
	if (keycode == 2)
		new_game->ray.strafe_right = 1;
	if (keycode == 0)
		new_game->ray.strafe_left = 1;
	if (keycode == 123)
		new_game->ray.rotate_left = 1;
	if (keycode == 124)
		new_game->ray.rotate_right = 1;
	if (keycode == 53)
		close_window(new_game);
	return (0);
}

int		key_release_hook(int keycode, t_mother *new_game)
{
	if (keycode == 13)
		new_game->ray.walk_forward = 0;
	if (keycode == 1)
		new_game->ray.walk_backward = 0;
	if (keycode == 2)
		new_game->ray.strafe_right = 0;
	if (keycode == 0)
		new_game->ray.strafe_left = 0;
	if (keycode == 123)
		new_game->ray.rotate_left = 0;
	if (keycode == 124)
		new_game->ray.rotate_right = 0;
	return (0);
}
#endif

#ifdef unix
int		key_press_hook(int keycode, t_mother *new_game)
{
	printf("%d\n", keycode);
	if (keycode == 119)
		new_game->ray.walk_forward = 1;
	if (keycode == 115)
		new_game->ray.walk_backward = 1;
	if (keycode == 100)
		new_game->ray.strafe_right = 1;
	if (keycode == 97)
		new_game->ray.strafe_left = 1;
	if (keycode == 65361)
		new_game->ray.rotate_left = 1;
	if (keycode == 65363)
		new_game->ray.rotate_right = 1;
	if (keycode == 65307)
		close_window(new_game);
	return (0);
}

int		key_release_hook(int keycode, t_mother *new_game)
{
	if (keycode == 119)
		new_game->ray.walk_forward = 0;
	if (keycode == 115)
		new_game->ray.walk_backward = 0;
	if (keycode == 100)
		new_game->ray.strafe_right = 0;
	if (keycode == 97)
		new_game->ray.strafe_left = 0;
	if (keycode == 65361)
		new_game->ray.rotate_left = 0;
	if (keycode == 65363)
		new_game->ray.rotate_right = 0;
	return (0);
}
#endif
