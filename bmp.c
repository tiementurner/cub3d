/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 14:13:01 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 15:30:35 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	write_bmp_header(t_map *map)
{
	unsigned int	size;
	unsigned int	offset;

	offset = 54;
	size = map->bmp_height * map->bmp_width * 4 + offset;
	write(map->bmp, "BM", 2);
	write(map->bmp, &size, 4);
	write(map->bmp, "\0\0\0\0", 4);
	write(map->bmp, &offset, 4);
}

void	write_bmp_infoheader(t_map *map)
{
	unsigned	int		size;
	unsigned	short	plane;
	unsigned	short	bbp;

	size = 40;
	plane = 1;
	bbp = 32;
	write(map->bmp, &size, 4);
	write(map->bmp, &map->bmp_width, 4);
	write(map->bmp, &map->bmp_height, 4);
	write(map->bmp, &plane, 2);
	write(map->bmp, &bbp, 2);
	write(map->bmp, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 24);
}

void	save_bmp(t_map *map, t_mlx *mlx)
{
	int				x;
	int				y;
	unsigned int	color;

	if (map->bmp_width > 16384)
		map->bmp_width = 16384;
	if (map->bmp_height > 16384)
		map->bmp_height = 16384;
	write_bmp_header(map);
	write_bmp_infoheader(map);
	y = map->bmp_height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < map->bmp_width)
		{
			color = *((unsigned int*)(mlx->addr + (y * mlx->line_length
					+ x * (mlx->bits_per_pixel / 8))));
			write(map->bmp, &color, 3);
			write(map->bmp, "\0", 1);
			x++;
		}
		y--;
	}
	exit(0);
}
