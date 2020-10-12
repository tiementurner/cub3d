/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 17:52:03 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/12 17:37:18 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		move(t_ray *ray, t_player *player, char **grid)
{
	if (ray->walk_forward == 1 || ray->walk_backward == 1)
		walk(ray, player, grid);
	if (ray->strafe_left == 1 || ray->strafe_right == 1)
		strafe(ray, player, grid);
	if (ray->rotate_left == 1 || ray->rotate_right == 1)
		rotate(player, ray);
	return (0);
}

void	walk(t_ray *ray, t_player *player, char **grid)
{
	if (ray->walk_forward == 1)
	{
		if (grid[(int)player->y][(int)(player->x + 0.5 * player->dir_x)] != '1')
			player->x += 0.1 * player->dir_x;
		if (grid[(int)(player->y + 0.5 * player->dir_y)][(int)player->x] != '1')
			player->y += 0.1 * player->dir_y;
	}
	if (ray->walk_backward == 1)
	{
		if (grid[(int)player->y][(int)(player->x - 0.5 * player->dir_x)] != '1')
			player->x -= 0.1 * player->dir_x;
		if (grid[(int)(player->y - 0.5 * player->dir_y)][(int)player->x] != '1')
			player->y -= 0.1 * player->dir_y;
	}
}

void	strafe(t_ray *ray, t_player *player, char **grid)
{
	if (ray->strafe_right == 1)
	{
		if (grid[(int)(player->y + 0.25 * ray->plane_y)][(int)player->x] != '1')
			player->y += 0.1 * ray->plane_y;
		if (grid[(int)player->y][(int)(player->x + 0.25 * ray->plane_x)] != '1')
			player->x += 0.1 * ray->plane_x;
	}
	if (ray->strafe_left == 1)
	{
		if (grid[(int)(player->y - 0.25 * ray->plane_y)][(int)player->x] != '1')
			player->y += 0.1 * (-1 * ray->plane_y);
		if (grid[(int)player->y][(int)(player->x - 0.25 * ray->plane_x)] != '1')
			player->x += 0.1 * (-1 * ray->plane_x);
	}
}

void	rotate(t_player *player, t_ray *ray)
{
	double	rs;
	double	old_dir;
	double	old_plane;

	rs = 0.08;
	if (ray->rotate_right == 1)
	{
		old_dir = player->dir_x;
		player->dir_x = player->dir_x * cos(-rs) - player->dir_y * sin(-rs);
		player->dir_y = old_dir * sin(-rs) + player->dir_y * cos(-rs);
		old_plane = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-rs) - ray->plane_y * sin(-rs);
		ray->plane_y = old_plane * sin(-rs) + ray->plane_y * cos(-rs);
	}
	if (ray->rotate_left == 1)
	{
		old_dir = player->dir_x;
		player->dir_x = player->dir_x * cos(rs) - player->dir_y * sin(rs);
		player->dir_y = old_dir * sin(rs) + player->dir_y * cos(rs);
		old_plane = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(rs) - ray->plane_y * sin(rs);
		ray->plane_y = old_plane * sin(rs) + ray->plane_y * cos(rs);
	}
}
