/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 16:48:26 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/09 16:15:42 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	count_sprites(t_map *map)
{
	int x;
	int y;

	x = 0;
	map->num_sprites = 0;
	while (map->grid[x])
	{
		y = 0;
		while (map->grid[x][y])
		{
			if (map->grid[x][y] == '2')
				map->num_sprites++;
			y++;
		}
		x++;
	}
	map->sprites = ft_calloc(map->num_sprites, sizeof(t_sprite));
	if (!map->sprites)
		put_error("Malloc error.");
}

void	set_sprite_values(t_map *map)
{
	int x;
	int y;
	int	spritecount;

	spritecount = 0;
	x = 0;
	y = 0;
	while (map->grid[x])
	{
		y = 0;
		while (map->grid[x][y])
		{
			if (map->grid[x][y] == '2')
			{
				map->sprites[spritecount].x = x + 0.5;
				map->sprites[spritecount].y = y + 0.5;
				spritecount++;
				map->grid[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}

void	init_sprites(t_map *map)
{
	count_sprites(map);
	set_sprite_values(map);
}

void	load_sprite(t_texture *sprite, void *mlx)
{
	sprite->img = mlx_xpm_file_to_image(mlx, sprite->path,
								&sprite->width, &sprite->height);
	if (!sprite->img)
		put_error("Failed to load sprite texture.");
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
									&sprite->line_length, &sprite->endian);
}
