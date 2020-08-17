/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:59 by tblanker      #+#    #+#                 */
/*   Updated: 2020/06/16 15:33:47 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void     draw(t_data *new_game)
{
    new_game->mlx = mlx_init();
    new_game->win = mlx_new_window(new_game->mlx, new_game->width, new_game->height, "Raycaster");
    new_game->img = mlx_new_image(new_game->mlx, new_game->width, new_game->height);
    new_game->addr = mlx_get_data_addr(new_game->img, &new_game->bits_per_pixel, &new_game->line_length, &new_game->endian);
	mlx_key_hook(new_game->win, print_keycode, new_game->mlx);
	mlx_hook(new_game->win, 02, 1L<<0, close_window, new_game);
	mlx_hook(new_game->win, 02, 1L<<0, move, new_game);
	mlx_loop_hook(new_game->mlx, render, new_game);
	//render(new_game);
	printf("%d, %d\n", new_game->width, new_game->height);
    mlx_loop(new_game->mlx);
}

int render(t_data *new_game)
{
	int		x;

	x = 0;
	while (x < new_game->width)
	{
		new_game->camera_X = 2 * x / (double)new_game->width - 1;
		new_game->raydir_X = new_game->dir_X + new_game->plane_X * new_game->camera_X;
		new_game->raydir_Y = new_game->dir_Y + new_game->plane_Y * new_game->camera_X;

		new_game->map_X = (int)new_game->player_X;
		new_game->map_Y = (int)new_game->player_Y;

		new_game->deltaDistX = sqrt(1 + pow(new_game->raydir_Y, 2) / pow(new_game->raydir_X, 2));
		new_game->deltaDistY = sqrt(1 + pow(new_game->raydir_X, 2) / pow(new_game->raydir_Y, 2));
		set_distance_to_sides(new_game);
		send_ray(new_game);
		if (new_game->side == 0)
			new_game->perpWallDist = (new_game->map_X - new_game->player_X + (1 - new_game->stepX) / 2) / new_game->raydir_X;
		else
			new_game->perpWallDist = (new_game->map_Y - new_game->player_Y + (1 - new_game->stepY) / 2) / new_game->raydir_Y;
		calculate_ray_length(new_game);
		draw_ray(new_game, x);
	  	x++;
	}
	mlx_put_image_to_window(new_game->mlx, new_game->win, new_game->img, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
