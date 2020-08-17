/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:59 by tblanker      #+#    #+#                 */
/*   Updated: 2020/08/16 15:48:30 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	initialize(t_player *player, t_ray *ray, char **grid)
{
	int x;
	int y;

	x = 0;
	while (grid[x])
	{
		y = 0;
		while (grid[x][y])
		{
			if (grid[x][y] != '1' && grid[x][y] != '2' &&
			grid[x][y] != '0')
			{
				set_start_value_player(x, y, player);
				set_start_value_ray(x, y, ray);
				grid[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}

void	set_start_value_player(int x, int y, t_player *player)
{
	player->player_X = x + 0.5;
	player->player_Y = y + 0.5;
	player->dir_X = 0;
	player->dir_Y = 1;
}

void	set_start_value(int x, int y, t_ray *ray)
{
	new_gameray->plane_X = 0.66;
	new_gameray->plane_Y = 0;
	if (new_gameray->grid[x][y] == 'S')
		new_gameray->dir_Y = -1;
	if (new_gameray->grid[x][y] == 'E')
	{
		new_gameray->dir_Y = 0;
		new_gameray->dir_X = 1;
		new_gameray->plane_X = 0;
		new_gameray->plane_Y = 0.66;
	}
	if (new_gameray->grid[x][y] == 'W')
	{
		new_gameray->dir_Y = 0;
		new_gameray->dir_X = -1;
		new_gameray->plane_X = 0;
		new_gameray->plane_Y = 0.66;
	}
}