/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 14:43:06 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/09 15:50:44 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	swap(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}

void	add_grid_line(t_map *new_map, char *line)
{
	char	**newgrid;
	int		i;

	i = 0;
	while (new_map->grid[i] != NULL)
		i++;
	newgrid = (char**)malloc(sizeof(char *) * (i + 2));
	if (!newgrid)
		put_error("Malloc error.");
	newgrid[i + 1] = NULL;
	i = 0;
	while (new_map->grid[i])
	{
		newgrid[i] = ft_strdup(new_map->grid[i]);
		free(new_map->grid[i]);
		i++;
	}
	free(new_map->grid);
	newgrid[i] = ft_strdup(line);
	new_map->grid = newgrid;
	new_map->grid_height = i + 1;
}

void	free_seperated_line(char **seperated_line)
{
	int i;

	i = 0;
	while (seperated_line[i])
	{
		free(seperated_line[i]);
		i++;
	}
	free(seperated_line);
}

void	set_tex_path(char *parameter, char *line, t_map *map, t_texture *tex)
{
	map->textures_parsed++;
	while (ft_strchr(parameter, *line))
		line++;
	tex->path = ft_strdup(line);
}

int		check_res_params(char **res)
{
	int	i;
	int j;

	i = 1;
	while (res[i])
	{
		j = 0;
		while (res[i][j])
		{
			if (!(ft_isdigit(res[i][j])))
				put_error("Please enter only numbers for resolution values.");
			j++;
		}
		i++;
	}
	return (i);
}
