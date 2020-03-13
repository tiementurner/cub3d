/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:05 by tblanker       #+#    #+#                */
/*   Updated: 2020/03/13 15:53:17 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parse(map *newmap, int fd)
{
	char	*line;
	int		end;

	while (end)
	{
		end = get_next_line(fd, &line);
		if (line[0] != '\0')
			set_map_specs(newmap, line);
	}
}

void	static set_map_specs(map *newmap, char *line)
{
	char **seperated_line;

	seperated_line = ft_split(line, ' ');
	if (ft_strncmp(seperated_line[0], "R", 1) == 0)
		set_resolution(newmap, seperated_line[1]);
	else if (ft_strncmp(seperated_line[0], "NO", 1) == 0)
		set_north_texture(newmap, seperated_line[1]);
	else if (ft_strncmp(seperated_line[0], "SO", 1) == 0)
		set_south_texture(newmap, seperated_line[1]);
	else if (ft_strncmp(seperated_line[0], "WE", 1) == 0)
		set_west_texture(newmap, seperated_line[1]);
	else if (ft_strncmp(seperated_line[0], "EA", 1) == 0)
		set_east_texture(newmap, seperated_line[1]);
	else if (ft_strncmp(seperated_line[0], "S", 1) == 0)
		set_south_texture(newmap, seperated_line[1]);
	else if (ft_strncmp(seperated_line[0], "F", 1) == 0)
		set_floor_color(newmap, seperated_line[1]);
	else if (ft_strncmp(seperated_line[0], "C", 1) == 0)
		set_ceiling_color(newmap, seperated_line[1]);
	else
		set_map_info(newmap, line);
}

void	set_map_info(map *newmap, char *line)
{
	
}