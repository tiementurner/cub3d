/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:59 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 15:37:49 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw(t_mother *new_game, t_mlx *mlx, t_mlx *mlx2)
{
	mlx->mlx = mlx_init();
	new_game->map.zbuffer = ft_calloc(new_game->map.width, sizeof(double));
	if (!new_game->map.zbuffer)
	{
		free_stuff(&new_game->map);
		put_error("Malloc error");
	}
	check_resolution(new_game, &new_game->map, mlx);
	mlx->win = mlx_new_window(mlx->mlx, new_game->map.width,
							new_game->map.height, "Raycaster");
	mlx->img = mlx_new_image(mlx->mlx, new_game->map.width,
							new_game->map.height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
								&mlx->line_length, &mlx->endian);
	mlx2->img = mlx_new_image(mlx->mlx, new_game->map.width,
								new_game->map.height);
	mlx2->addr = mlx_get_data_addr(mlx2->img, &mlx2->bits_per_pixel,
								&mlx2->line_length, &mlx2->endian);
	new_game->mlx.img_count = 0;
	load_textures(&new_game->map, new_game->mlx.mlx);
	load_sprite(&new_game->map.sprite, new_game->mlx.mlx);
	mlx_hook(mlx->win, 17, 1L << 17, &close_window, new_game);
	mlx_hook(mlx->win, 02, 1L << 0, &move_hook, new_game);
	mlx_loop_hook(mlx->mlx, render, new_game);
	mlx_loop(mlx->mlx);
}

int		render(t_mother *new_game)
{
	if (new_game->mlx.img_count > 10000)
		new_game->mlx.img_count = 0;
	if (new_game->mlx.img_count % 2 == 0)
	{
		d_d_a(&new_game->ray, &new_game->player, &new_game->map,
				&new_game->mlx);
		mlx_put_image_to_window(new_game->mlx.mlx, new_game->mlx.win,
										new_game->mlx.img, 0, 0);
	}
	if (new_game->mlx.img_count % 2 == 1 && new_game->map.bmp == 0)
	{
		d_d_a(&new_game->ray, &new_game->player,
		&new_game->map, &new_game->mlx2);
		mlx_put_image_to_window(new_game->mlx.mlx, new_game->mlx.win,
										new_game->mlx2.img, 0, 0);
	}
	new_game->mlx.img_count++;
	return (0);
}

void	d_d_a(t_ray *ray, t_player *player, t_map *map, t_mlx *mlx)
{
	ray->x = 0;
	while (ray->x < map->width)
	{
		init_ray(ray, player, map);
		set_distance_to_sides(player, ray);
		send_ray(ray, map->grid);
		if (ray->side == 0)
			ray->perpwalldist = (ray->map_x - player->x +
			(1 - ray->step_x) / 2) / ray->dir_x;
		else
			ray->perpwalldist = (ray->map_y - player->y +
			(1 - ray->step_y) / 2) / ray->dir_y;
		calculate_draw_data(ray, player, map->height);
		draw_ray(ray, map, mlx);
		map->zbuffer[ray->x] = ray->perpwalldist;
		ray->x++;
	}
	sprites(map, player, ray, mlx);
}
