/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:05 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/09 16:04:54 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_map_specs(t_map *new_map, char *line)
{
	char	**seperated_line;
	int		i;

	i = 0;
	seperated_line = ft_split(line, ' ');
	if (ft_strncmp(seperated_line[0], "R", 1) == 0)
		set_resolution(new_map, seperated_line);
	else if (ft_strncmp(seperated_line[0], "NO", 2) == 0)
		set_tex_path("NO ", line, new_map, &new_map->north);
	else if (ft_strncmp(seperated_line[0], "SO", 2) == 0)
		set_tex_path("SO ", line, new_map, &new_map->south);
	else if (ft_strncmp(seperated_line[0], "WE", 2) == 0)
		set_tex_path("WE ", line, new_map, &new_map->west);
	else
	{
		set_map_specs_second(new_map, line, seperated_line);
		i = 1;
	}
	if (i == 0)
		free_seperated_line(seperated_line);
}

void	set_floor_ceiling(t_map *new_map, char **rgb, char cf)
{
	char	**color_ints;
	char	*good_rgb;
	int		i;

	i = 0;
	good_rgb = correct_rgb_values(rgb);
	color_ints = ft_split(good_rgb, ',');
	free(good_rgb);
	while (color_ints[i])
	{
		if ((ft_atoi(color_ints[i]) > 255 || ft_atoi(color_ints[i]) < 0))
			put_error("Invalid rgb values for floor or ceiling.");
		i++;
	}
	if (i != 3)
		put_error("Not enough RGB values for floor or ceiling color");
	assign_cf_colors(new_map, color_ints, cf);
	free_seperated_line(color_ints);
}

void	set_resolution(t_map *new_map, char **res)
{
	if (check_res_params(res) != 3)
		put_error("Resolution not correctly specified.");
	if (ft_atoi_long(res[1]) <= 0 || ft_atoi_long(res[2]) <= 0)
		put_error("Resolution size not positive values.");
	if (ft_atoi_long(res[1]) >= 2147483648)
		new_map->width = 2147483647;
	if (ft_atoi_long(res[2]) >= 2147483648)
		new_map->height = 2147483647;
	else
	{
		new_map->width = ft_atoi_long(res[1]);
		new_map->height = ft_atoi_long(res[2]);
	}
}

void	set_grid(t_map *new_map, char *line)
{
	char	**newgrid;
	int		i;

	i = 0;
	if (!(new_map->grid))
	{
		newgrid = (char**)malloc(sizeof(char *) * 2);
		if (!newgrid)
			put_error("Malloc error.");
		newgrid[1] = NULL;
		newgrid[0] = ft_strdup(line);
		new_map->grid = newgrid;
	}
	else
		add_grid_line(new_map, line);
}

void	parse(t_map *new_map, int fd)
{
	char	*line;
	int		end;
	int		empty_line;

	new_map->textures_parsed = 0;
	new_map->grid_parsed = 0;
	empty_line = 0;
	end = 1;
	while (end)
	{
		if (new_map->grid_parsed && empty_line)
			put_error("Empty line detected in map.");
		end = get_next_line(fd, &line);
		if (line[0] != '\0')
		{
			empty_line = 0;
			set_map_specs(new_map, line);
			free(line);
		}
		else
		{
			empty_line = 1;
			free(line);
		}
	}
}
