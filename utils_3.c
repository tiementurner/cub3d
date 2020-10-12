/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 16:02:41 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/12 17:57:10 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	assign_cf_colors(t_map *map, char **color_ints, char cf)
{
	if (cf == 'c')
	{
		map->ceiling_color = (65536 * (ft_atoi(color_ints[0])) +
		256 * (ft_atoi(color_ints[1])) + (ft_atoi(color_ints[2])));
	}
	if (cf == 'f')
	{
		map->floor_color = (65536 * (ft_atoi(color_ints[0])) +
		256 * (ft_atoi(color_ints[1])) + (ft_atoi(color_ints[2])));
	}
}
