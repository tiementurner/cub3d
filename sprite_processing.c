/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_processing.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 18:32:51 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/09 17:59:35 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	sprites(t_map *map, t_player *player, t_ray *ray, t_mlx *mlx)
{
	int	i;
	int	sprite_order[map->num_sprites];
	int	sprite_distance[map->num_sprites];

	i = 0;
	while (i < map->num_sprites)
	{
		sprite_order[i] = i;
		sprite_distance[i] = pow((player->x - map->sprites[i].y), 2)
							+ pow((player->y - map->sprites[i].x), 2);
		i++;
	}
	order_sprites(sprite_order, sprite_distance, map);
	i = 0;
	while (i < map->num_sprites)
	{
		calc_sprite(map, player, map->sprites[sprite_order[i]], ray);
		draw_sprite(map, ray, mlx);
		i++;
	}
}

void	order_sprites(int *sprite_order, int *sprite_distance, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->num_sprites - 1)
	{
		j = 0;
		while (j < map->num_sprites - i - 1)
		{
			if (sprite_distance[j] < sprite_distance[j + 1])
			{
				swap(&sprite_distance[j], &sprite_distance[j + 1]);
				swap(&sprite_order[j], &sprite_order[j + 1]);
			}
			j++;
		}
		i++;
	}
}

void	calc_sprite(t_map *map, t_player *player, t_sprite sprite, t_ray *ray)
{
	double	sprite_x;
	double	sprite_y;

	sprite_y = sprite.x - player->y;
	sprite_x = sprite.y - player->x;
	ray->invdet = 1.0 / (ray->plane_x * player->dir_y
						- player->dir_x * ray->plane_y);
	ray->transformx = ray->invdet * (player->dir_y * sprite_x
									- player->dir_x * sprite_y);
	ray->transformy = ray->invdet * (-ray->plane_y * sprite_x
									+ ray->plane_x * sprite_y);
	ray->spritescreenx = (int)((map->width / 2) *
						(1 + ray->transformx / ray->transformy));
	sprite_draw_data(map, ray);
}

void	sprite_draw_data(t_map *map, t_ray *ray)
{
	ray->spriteheight = fabs((map->height / (ray->transformy)));
	ray->spritestarty = -ray->spriteheight / 2 + map->height / 2;
	if (ray->spritestarty < 0)
		ray->spritestarty = 0;
	ray->spriteendy = ray->spriteheight / 2 + map->height / 2;
	if (ray->spriteendy >= map->height)
		ray->spriteendy = map->height - 1;
	ray->spritewidth = fabs((map->height / (ray->transformy)));
	ray->spritestartx = -(ray->spritewidth) / 2 + ray->spritescreenx;
	if (ray->spritestartx < 0)
		ray->spritestartx = 0;
	ray->spriteendx = ray->spritewidth / 2 + ray->spritescreenx;
	if (ray->spriteendx >= map->width)
		ray->spriteendx = map->width - 1;
}

void	draw_sprite(t_map *map, t_ray *ray, t_mlx *mlx)
{
	int				tex_x;
	int				tex_y;
	int				y;
	int				d;
	unsigned int	color;

	ray->stripe = ray->spritestartx;
	while (ray->stripe < ray->spriteendx)
	{
		tex_x = (int)(256 * (ray->stripe - (-ray->spritewidth / 2 +
		ray->spritescreenx)) * map->sprite.width / ray->spritewidth) / 256;
		y = ray->spritestarty;
		if (ray->transformy > 0 && ray->stripe > 0 && ray->stripe < map->width
		&& ray->transformy < map->zbuffer[ray->stripe])
			while (y < ray->spriteendy)
			{
				d = (y) * 256 - map->height * 128 + ray->spriteheight * 128;
				tex_y = ((d * map->sprite.height) / ray->spriteheight) / 256;
				color = retrieve_texture_pixel(&map->sprite, tex_x, tex_y);
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(mlx, ray->stripe, y, color);
				y++;
			}
		ray->stripe++;
	}
}
