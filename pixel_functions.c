/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixel_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 18:31:37 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/09 14:19:15 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void			my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	retrieve_texture_pixel(t_texture *data, int x, int y)
{
	unsigned int color;

	color = *((unsigned int*)(data->addr + (y * data->line_length)
	+ (x * data->bits_per_pixel / 8)));
	return (color);
}
