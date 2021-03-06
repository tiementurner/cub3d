/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/06 18:25:10 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/12 17:56:12 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*correct_rgb_values(char **rgb)
{
	int i;
	int j;
	int k;

	k = 0;
	i = 1;
	if ((rgb[0][0] == 'F' || rgb[0][0] == 'C') && rgb[0][1] != '\0')
		put_error("Incorrect floor or ceiling color specifications");
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!(ft_isdigit(rgb[i][j])) && rgb[i][j] != ',')
				put_error("Please enter only positive rgb values under 255.");
			j++;
			k++;
		}
		i++;
	}
	return (concat_rgb(rgb, k));
}

char	*concat_rgb(char **rgb, int k)
{
	char	*p;
	int		i;
	int		j;
	int		c;

	i = 1;
	c = 0;
	p = (char *)malloc(sizeof(char) * k + 1);
	if (!p)
		put_error("Malloc error.");
	p[k] = '\0';
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			p[c] = rgb[i][j];
			c++;
			j++;
		}
		i++;
	}
	return (p);
}

void	check_resolution(t_mother *ng, t_map *map, t_mlx *mlx)
{
	int	max_height;
	int	max_width;

	map->bmp_w = map->width;
	map->bmp_h = map->height;
	if (map->bmp_w > 16384)
		map->bmp_w = 16384;
	if (map->bmp_h > 16384)
		map->bmp_h = 16384;
	if (ng->map.bmp != 0)
	{
		// mlx->win = mlx_new_window(mlx->mlx, ng->map.bmp_w,
		// ng->map.bmp_h, "Raycaster");
		mlx->img = mlx_new_image(mlx->mlx, ng->map.bmp_w, ng->map.bmp_h);
		mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
		&mlx->line_length, &mlx->endian);
		load_textures(mlx, &ng->map, ng->mlx.mlx);
		load_sprite(&ng->map.sprite, ng->mlx.mlx);
		render(ng);
		save_bmp(&ng->map, mlx);
	}
	mlx_get_screen_size(mlx->mlx, &max_width, &max_height);
	if (map->width > max_width)
		map->width = max_width;
	if (map->height > max_height)
		map->height = max_height;
}

void	set_map_specs_second(t_map *new_map, char *line, char **seperated_line)
{
	if (ft_strncmp(seperated_line[0], "EA", 2) == 0)
		set_tex_path("EA ", line, new_map, &new_map->east);
	else if (ft_strncmp(seperated_line[0], "S", 1) == 0)
		set_tex_path("S ", line, new_map, &new_map->sprite);
	else if (ft_strncmp(seperated_line[0], "F", 1) == 0)
		set_floor_ceiling(new_map, seperated_line, 'f');
	else if (ft_strncmp(seperated_line[0], "C", 1) == 0)
		set_floor_ceiling(new_map, seperated_line, 'c');
	else if (ft_strchr("012NSEW ", seperated_line[0][0]))
	{
		new_map->grid_parsed = 1;
		set_grid(new_map, line);
	}
	else
		put_error("something is wrong with your map data");
	free_seperated_line(seperated_line);
}
