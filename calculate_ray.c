/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_ray.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:59 by tblanker      #+#    #+#                 */
/*   Updated: 2020/06/17 13:35:18 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_distance_to_sides(t_data *new_game)
{
	if (new_game->raydir_X < 0)
	{
		new_game->stepX = -1;
		new_game->sideDistX = (new_game->player_X - new_game->map_X) * new_game->deltaDistX;
	}
	else
	{
		new_game->stepX = 1;
		new_game->sideDistX = (new_game->map_X + 1.0 - new_game->player_X) * new_game->deltaDistX;
	}
	if (new_game->raydir_Y < 0)
	{
		new_game->stepY = -1;
		new_game->sideDistY = (new_game->player_Y - new_game->map_Y) * new_game->deltaDistY;
	}
	else
	{
		new_game->stepY = 1;
		new_game->sideDistY = (new_game->map_Y + 1.0 - new_game->player_Y) * new_game->deltaDistY;
	}
}

void	send_ray(t_data *new_game)
{
	new_game->hit = 0;
	while (new_game->hit == 0)
	{
		if (new_game->sideDistX < new_game->sideDistY)
		{
			new_game->sideDistX += new_game->deltaDistX;
			new_game->map_X += new_game->stepX;
			new_game->side = 0;
		}
		else
		{
			new_game->sideDistY += new_game->deltaDistY;
			new_game->map_Y += new_game->stepY;
			new_game->side = 1;
		}
		if (new_game->grid[new_game->map_X][new_game->map_Y] == '1')
			new_game->hit = 1;
	}
}

void	calculate_ray_length(t_data *new_game)
{
	int h;
	int lineheight;

	h = new_game->height;
	lineheight = (int)(h / new_game->perpWallDist);
	new_game->drawStart = -lineheight / 2 + h / 2;
	if (new_game->drawStart < 0)
		new_game->drawStart = 0;
	new_game->drawEnd = lineheight / 2 + h / 2;
	if (new_game->drawEnd >= h)
		new_game->drawEnd = h - 1;
}

void	draw_ray(t_data *new_game, int x)
{
	int				y;
	unsigned int	color;

	color = 0xFF00000;
	if (new_game->side == 1)
		color = color / 2;
	y = 0;
	while (y < new_game->height)
	{
		if (y < new_game->height / 2)
			my_mlx_pixel_put(new_game, x, y, new_game->ceiling_color);
		if (y > new_game->height / 2)
			my_mlx_pixel_put(new_game, x, y, new_game->floor_color);
		if (y > new_game->drawStart && y < new_game->drawEnd)
			my_mlx_pixel_put(new_game, x, y, color);
		y++;
	}
}
