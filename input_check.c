/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 16:50:00 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/09 17:33:09 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	valid_input_check(int argc, char **argv, t_map *map)
{
	int i;

	i = 0;
	if (argv[1])
		check_valid_file(argv[1]);
	if (argc < 2 || argc > 3)
		put_error("invalid amount of arguments.");
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
		map->bmp = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 7) != 0)
		put_error("Invalid third argument. Did you mean: '--save'?");
}

void	check_valid_file(char *file)
{
	int i;

	i = 0;
	while (file[i] != '.' && file[i])
		i++;
	if (file[i] != '.')
		put_error("Invalid file. '.cub' file needed.");
	if (ft_strncmp(&file[i], ".cub", 4) != 0)
		put_error("Invalid file. '.cub' file needed.");
	while (file[i] != 'b')
		i++;
	if (file[i + 1] != '\0')
		put_error("Invalid file. '.cub' file needed.");
}

void	check_valid_grid(char **grid)
{
	int i;
	int j;
	int	startpos;

	startpos = 0;
	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (!(ft_strchr("012NSEW ", grid[i][j])))
				put_error("Invalid character in grid detected.");
			if (ft_strchr("NSEW", grid[i][j]))
				startpos++;
			j++;
		}
		i++;
	}
	if (startpos != 1)
		put_error("Invalid amount of start positions.");
}

void	flood_fill(t_map *map, t_player *player)
{
	int		i;
	int		j;

	flood_fill_check(player->y - 0.5, player->x - 0.5,
						map->grid, map->grid_height);
	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'V')
				map->grid[i][j] = '0';
			j++;
		}
		i++;
	}
}

void	flood_fill_check(int x, int y, char **grid, int height)
{
	if (x > height - 1 || x < 0 || y > (int)(ft_strlen(grid[x]) - 1) || y < 0
	|| grid[x][y] == ' ')
		put_error("Grid is not fully enclosed by walls.");
	if (grid[x][y] == '1' || grid[x][y] == 'V')
		return ;
	if (grid[x][y] == '0')
		grid[x][y] = 'V';
	flood_fill_check(x + 1, y, grid, height);
	flood_fill_check(x + 1, y + 1, grid, height);
	flood_fill_check(x + 1, y - 1, grid, height);
	flood_fill_check(x - 1, y, grid, height);
	flood_fill_check(x - 1, y + 1, grid, height);
	flood_fill_check(x - 1, y - 1, grid, height);
	flood_fill_check(x, y + 1, grid, height);
	flood_fill_check(x, y - 1, grid, height);
}
