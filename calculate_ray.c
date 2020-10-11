/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_ray.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:59 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/09 17:33:09 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_ray(t_ray *ray, t_player *player, t_map *map)
{
	ray->camera_x = 2 * ray->x / (double)map->width - 1;
	ray->dir_x = player->dir_x + ray->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->deltadistx = sqrt(1 + pow(ray->dir_y, 2) / pow(ray->dir_x, 2));
	ray->deltadisty = sqrt(1 + pow(ray->dir_x, 2) / pow(ray->dir_y, 2));
}

void	set_distance_to_sides(t_player *player, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedistx = (player->x - ray->map_x) * ray->deltadistx;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedistx = (ray->map_x + 1.0 - player->x) * ray->deltadistx;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedisty = (player->y - ray->map_y) * ray->deltadisty;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedisty = (ray->map_y + 1.0 - player->y) * ray->deltadisty;
	}
}

void	send_ray(t_ray *ray, char **grid)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_draw_data(t_ray *ray, t_player *player, int height)
{
	ray->lineheight = (int)(height / ray->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + height / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + height / 2;
	if (ray->drawend >= height)
		ray->drawend = height - 1;
	if (ray->side == 0)
		ray->wall_x = player->y + ray->perpwalldist * ray->dir_y;
	else
		ray->wall_x = player->x + ray->perpwalldist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	draw_ray(t_ray *ray, t_map *map, t_mlx *mlx)
{
	unsigned int	color;

	ray->y = 0;
	while (ray->y < map->height)
	{
		if (ray->y < map->height / 2)
			my_mlx_pixel_put(mlx, ray->x, ray->y, map->ceiling_color);
		if (ray->y > map->height / 2)
			my_mlx_pixel_put(mlx, ray->x, ray->y, map->floor_color);
		if (ray->y >= ray->drawstart && ray->y < ray->drawend)
		{
			color = texture_picker(ray, map);
			my_mlx_pixel_put(mlx, ray->x, ray->y, color);
		}
		ray->y++;
	}
}
