/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 14:13:01 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/12 17:56:30 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	write_bmp_header(t_map *map)
{
	unsigned int	size;
	unsigned int	offset;

	offset = 54;
	size = map->bmp_h * map->bmp_w * 4 + offset;
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
	write(map->bmp, &map->bmp_w, 4);
	write(map->bmp, &map->bmp_h, 4);
	write(map->bmp, &plane, 2);
	write(map->bmp, &bbp, 2);
	write(map->bmp, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 24);
}

void	save_bmp(t_map *map, t_mlx *mlx)
{
	int				x;
	int				y;
	unsigned int	color;

	write_bmp_header(map);
	write_bmp_infoheader(map);
	y = map->bmp_h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < map->bmp_w)
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
