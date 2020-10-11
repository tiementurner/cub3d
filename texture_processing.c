/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_processing.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 16:29:21 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/09 17:24:27 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static	unsigned	int		north_texture(t_ray *ray, t_map *map)
{
	unsigned int	color;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;

	step = 1.0 * map->north.height / ray->lineheight;
	tex_pos = (ray->drawstart - map->height / 2 + ray->lineheight / 2) * step;
	tex_pos += ((ray->y - ray->drawstart) * step);
	tex_x = (ray->wall_x * (double)map->north.width);
	tex_y = (int)tex_pos & (map->north.height - 1);
	color = retrieve_texture_pixel(&map->north, tex_x, tex_y);
	return (color);
}

static	unsigned	int		south_texture(t_ray *ray, t_map *map)
{
	unsigned int	color;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;

	step = 1.0 * map->south.height / ray->lineheight;
	tex_pos = (ray->drawstart - map->height / 2 + ray->lineheight / 2) * step;
	tex_pos += ((ray->y - ray->drawstart) * step);
	tex_x = (ray->wall_x * (double)map->south.width);
	tex_y = (int)tex_pos & (map->south.height - 1);
	color = retrieve_texture_pixel(&map->south, tex_x, tex_y);
	return (color);
}

static	unsigned	int		west_texture(t_ray *ray, t_map *map)
{
	unsigned int	color;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;

	step = 1.0 * map->west.height / ray->lineheight;
	tex_pos = (ray->drawstart - map->height / 2 + ray->lineheight / 2) * step;
	tex_pos += ((ray->y - ray->drawstart) * step);
	tex_x = (ray->wall_x * (double)map->west.width);
	tex_y = (int)tex_pos & (map->west.height - 1);
	color = retrieve_texture_pixel(&map->west, tex_x, tex_y);
	return (color);
}

static	unsigned	int		east_texture(t_ray *ray, t_map *map)
{
	unsigned int	color;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;

	step = 1.0 * map->east.height / ray->lineheight;
	tex_pos = (ray->drawstart - map->height / 2 + ray->lineheight / 2) * step;
	tex_pos += ((ray->y - ray->drawstart) * step);
	tex_x = (ray->wall_x * (double)map->east.width);
	tex_y = (int)tex_pos & (map->east.height - 1);
	color = retrieve_texture_pixel(&map->east, tex_x, tex_y);
	return (color);
}

unsigned int				texture_picker(t_ray *ray, t_map *map)
{
	if (ray->side == 0 && ray->dir_x > 0)
		return (west_texture(ray, map));
	if (ray->side == 0 && ray->dir_x < 0)
		return (east_texture(ray, map));
	if (ray->side == 1 && ray->dir_y > 0)
		return (south_texture(ray, map));
	if (ray->side == 1 && ray->dir_y < 0)
		return (north_texture(ray, map));
	return (0);
}
