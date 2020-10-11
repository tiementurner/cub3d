/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:49:59 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/09 17:33:09 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	initialize(t_player *player, t_ray *ray, char **grid)
{
	int x;
	int y;

	x = 0;
	while (grid[x])
	{
		y = 0;
		while (grid[x][y])
		{
			if (grid[x][y] != '1' && grid[x][y] != '2' &&
			grid[x][y] != '0' && grid[x][y] != ' ')
			{
				set_start_value_player(x, y, player, grid);
				set_start_value_ray(x, y, ray, grid);
				grid[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}

char	*ft_strrev(char *str)
{
	int		i;
	char	*p1;
	int		length;

	length = ft_strlen(str);
	i = 0;
	p1 = (char *)malloc(sizeof(char) * length + 1);
	if (!p1)
		put_error("Malloc error.");
	p1[length] = '\0';
	while (i < length)
	{
		p1[i] = str[length - i - 1];
		i++;
	}
	return (p1);
}

void	rotate_grid(t_map *map)
{
	char	**rotated_grid;
	int		i;
	int		j;

	j = map->grid_height - 1;
	rotated_grid = (char **)malloc(sizeof(char *) * map->grid_height + 1);
	if (!rotated_grid)
		put_error("Malloc error.");
	i = 0;
	while (i < map->grid_height)
	{
		rotated_grid[i] = ft_strdup(map->grid[j]);
		free(map->grid[j]);
		i++;
		j--;
	}
	free(map->grid);
	rotated_grid[i] = NULL;
	map->grid = rotated_grid;
}

void	set_start_value_player(int x, int y, t_player *player, char **grid)
{
	player->x = y + 0.5;
	player->y = x + 0.5;
	player->dir_x = 0;
	player->dir_y = 1;
	if (grid[x][y] == 'S')
		player->dir_y = -1;
	if (grid[x][y] == 'E')
	{
		player->dir_y = 0;
		player->dir_x = 1;
	}
	if (grid[x][y] == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

void	set_start_value_ray(int x, int y, t_ray *ray, char **grid)
{
	ray->plane_x = 0.66;
	ray->plane_y = 0;
	if (grid[x][y] == 'S')
		ray->plane_x = -0.66;
	if (grid[x][y] == 'E')
	{
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
	if (grid[x][y] == 'W')
	{
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
}
