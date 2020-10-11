/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 17:52:03 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/09 17:33:09 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		move_hook(int keycode, t_mother *new_game)
{
	if (keycode == 53)
		close_window(new_game);
	move(keycode, &new_game->ray, &new_game->player, new_game->map.grid);
	return (0);
}

int		move(int keycode, t_ray *ray, t_player *player, char **grid)
{
	if (keycode == 13 || keycode == 1 || keycode == 119 || keycode == 115)
		walk(keycode, player, grid);
	if (keycode == 0 || keycode == 2 || keycode == 97 || keycode == 100)
		strafe(keycode, ray, player, grid);
	if (keycode == 124 || keycode == 123 || keycode == 65363 ||
		keycode == 65361)
		rotate(keycode, player, ray);
	return (0);
}

void	walk(int keycode, t_player *player, char **grid)
{
	if (keycode == 13 || keycode == 119)
	{
		if (grid[(int)player->y][(int)(player->x + 0.5 * player->dir_x)] != '1')
			player->x += 0.25 * player->dir_x;
		if (grid[(int)(player->y + 0.5 * player->dir_y)][(int)player->x] != '1')
			player->y += 0.25 * player->dir_y;
	}
	if (keycode == 1 || keycode == 115)
	{
		if (grid[(int)player->y][(int)(player->x - 0.5 * player->dir_x)] != '1')
			player->x -= 0.25 * player->dir_x;
		if (grid[(int)(player->y - 0.5 * player->dir_y)][(int)player->x] != '1')
			player->y -= 0.25 * player->dir_y;
	}
}

void	strafe(int keycode, t_ray *ray, t_player *player, char **grid)
{
	if (keycode == 2 || keycode == 100)
	{
		if (grid[(int)(player->y + 0.25 * ray->plane_y)][(int)player->x] != '1')
			player->y += 0.25 * ray->plane_y;
		if (grid[(int)player->y][(int)(player->x + 0.25 * ray->plane_x)] != '1')
			player->x += 0.25 * ray->plane_x;
	}
	if (keycode == 0 || keycode == 97)
	{
		if (grid[(int)(player->y - 0.25 * ray->plane_y)][(int)player->x] != '1')
			player->y += 0.25 * (-1 * ray->plane_y);
		if (grid[(int)player->y][(int)(player->x - 0.25 * ray->plane_x)] != '1')
			player->x += 0.25 * (-1 * ray->plane_x);
	}
}

void	rotate(int keycode, t_player *player, t_ray *ray)
{
	double	rs;
	double	old_dir;
	double	old_plane;

	rs = 0.12;
	if (keycode == 124 || keycode == 65363)
	{
		old_dir = player->dir_x;
		player->dir_x = player->dir_x * cos(-rs) - player->dir_y * sin(-rs);
		player->dir_y = old_dir * sin(-rs) + player->dir_y * cos(-rs);
		old_plane = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-rs) - ray->plane_y * sin(-rs);
		ray->plane_y = old_plane * sin(-rs) + ray->plane_y * cos(-rs);
	}
	if (keycode == 123 || keycode == 65361)
	{
		old_dir = player->dir_x;
		player->dir_x = player->dir_x * cos(rs) - player->dir_y * sin(rs);
		player->dir_y = old_dir * sin(rs) + player->dir_y * cos(rs);
		old_plane = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(rs) - ray->plane_y * sin(rs);
		ray->plane_y = old_plane * sin(rs) + ray->plane_y * cos(rs);
	}
}
