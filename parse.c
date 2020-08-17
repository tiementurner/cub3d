/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:05 by tblanker      #+#    #+#                 */
/*   Updated: 2020/08/16 15:35:02 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void set_map_specs(t_map *new_map, char *line)
{
	char **seperated_line;

	seperated_line = ft_split(line, ' ');
	if (ft_strncmp(seperated_line[0], "R", 1) == 0)
		set_resolution(new_map, seperated_line);
	else if (ft_strncmp(seperated_line[0], "NO", 1) == 0)
		new_map->north = seperated_line[1];
	else if (ft_strncmp(seperated_line[0], "SO", 1) == 0)
		new_map->south = seperated_line[1];
	else if (ft_strncmp(seperated_line[0], "WE", 1) == 0)
		new_map->west = seperated_line[1];
	else if (ft_strncmp(seperated_line[0], "EA", 1) == 0)
		new_map->east = seperated_line[1];
	else if (ft_strncmp(seperated_line[0], "S", 1) == 0)
		new_map->sprite = seperated_line[1];
	else if (ft_strncmp(seperated_line[0], "F", 1) == 0)
		set_floor_ceiling(new_map, seperated_line[1], 'f');
	else if (ft_strncmp(seperated_line[0], "C", 1) == 0)
		set_floor_ceiling(new_map, seperated_line[1], 'c');
	else
		set_grid(new_map, line);
}

void set_floor_ceiling(t_map *new_map, char *rgb, char cf)
{
	char **color_ints;

	color_ints = ft_split(rgb, ',');
	if (cf == 'c')
	{
		new_map->ceiling_color = ((ft_atoi(color_ints[0]) + 1) *
		(ft_atoi(color_ints[1]) + 1) * (ft_atoi(color_ints[2]) + 1) * 16 - 16);
	}
	if (cf == 'f')
	{
		new_map->floor_color = ((ft_atoi(color_ints[0]) + 1) *
		(ft_atoi(color_ints[1]) + 1) * (ft_atoi(color_ints[2]) + 1) * 16 - 16);
	}
}

void	set_resolution(t_map *new_map, char **res)
{
	new_map->width = ft_atoi(res[1]);
	new_map->height = ft_atoi(res[2]);
}

void	set_grid(t_map *new_map, char *line)
{
	char	**newgrid;
	int		i;

	i = 0;
	if (!(new_map->grid))
	{
		newgrid = (char**)malloc(sizeof(char *) * 2);
		newgrid[1] = NULL;
		newgrid[0] = ft_strdup(line);
		new_map->grid = newgrid;
	}
	else
	{
		while (new_map->grid[i] != NULL)
			i++;
		newgrid = (char**)malloc(sizeof(char *) * (i + 2));
		newgrid[i + 1] = NULL;
		i = 0;
		while (new_map->grid[i])
		{
			newgrid[i] = ft_strdup(new_map->grid[i]);
			i++;
		}
		newgrid[i] = ft_strdup(line);
		new_map->grid = newgrid;
	}
}

void	parse(t_map *new_map, int fd)
{
	char	*line;
	int		end;

	end = 1;
	while (end)
	{
		end = get_next_line(fd, &line);
		if (line[0] != '\0')
			set_map_specs(new_map, line);
	}
}
