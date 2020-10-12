/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_loader.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 17:39:22 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/12 17:50:52 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static	void	load_north_texture(t_texture *north, void *mlx)
{
	north->img = mlx_xpm_file_to_image(mlx, north->path, &north->width,
											&north->height);
	if (!north->img)
		put_error("Failed to load north texture, please check texture-path");
	north->addr = mlx_get_data_addr(north->img, &north->bits_per_pixel,
									&north->line_length, &north->endian);
	free(north->path);
}

static	void	load_south_texture(t_texture *south, void *mlx)
{
	south->img = mlx_xpm_file_to_image(mlx, south->path, &south->width,
											&south->height);
	if (!south->img)
		put_error("Failed to load south texture, please check texture-path");
	south->addr = mlx_get_data_addr(south->img, &south->bits_per_pixel,
									&south->line_length, &south->endian);
	free(south->path);
}

static	void	load_west_texture(t_texture *west, void *mlx)
{
	west->img = mlx_xpm_file_to_image(mlx, west->path, &west->width,
											&west->height);
	if (!west->img)
		put_error("Failed to load west texture, please check texture-path");
	west->addr = mlx_get_data_addr(west->img, &west->bits_per_pixel,
									&west->line_length, &west->endian);
	free(west->path);
}

static	void	load_east_texture(t_texture *east, void *mlx)
{
	east->img = mlx_xpm_file_to_image(mlx, east->path, &east->width,
											&east->height);
	if (!east->img)
		put_error("Failed to load east texture, please check texture-path");
	east->addr = mlx_get_data_addr(east->img, &east->bits_per_pixel,
									&east->line_length, &east->endian);
	free(east->path);
}

void			load_textures(t_mlx *mlx_struct, t_map *map, void *mlx)
{
	mlx_struct->img_count = 0;
	load_north_texture(&map->north, mlx);
	load_south_texture(&map->south, mlx);
	load_west_texture(&map->west, mlx);
	load_east_texture(&map->east, mlx);
}
