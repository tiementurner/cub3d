/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:50:58 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/12 17:55:21 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

# include "minilibx-mac/mlx.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef	struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_count;
}				t_mlx;

typedef	struct	s_ray {
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		sidedistx;
	double		sidedisty;
	double		camera_x;
	double		deltadistx;
	double		deltadisty;
	double		plane_x;
	double		plane_y;
	int			side;
	int			hit;
	int			step_x;
	int			step_y;
	double		perpwalldist;
	int			drawstart;
	int			drawend;
	double		wall_x;
	int			lineheight;
	int			x;
	int			y;
	double		transformx;
	double		transformy;
	double		invdet;
	int			spritescreenx;
	int			spriteheight;
	int			spritewidth;
	int			spritestartx;
	int			spritestarty;
	int			spriteendx;
	int			spriteendy;
	int			stripe;
	int			walk_forward;
	int			walk_backward;
	int			strafe_left;
	int			strafe_right;
	int			rotate_left;
	int			rotate_right;
}				t_ray;

typedef	struct	s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
}				t_player;

typedef struct	s_texture
{
	void		*img;
	int			height;
	int			width;
	char		*path;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_texture;

typedef	struct	s_sprite
{
	double	x;
	double	y;
}				t_sprite;

typedef	struct	s_map
{
	int			height;
	int			width;
	int			resolution[2];
	t_texture	north;
	t_texture	west;
	t_texture	east;
	t_texture	south;
	t_texture	sprite;
	int			floor_color;
	int			ceiling_color;
	char		**grid;
	int			grid_height;
	double		*zbuffer;
	int			num_sprites;
	t_sprite	*sprites;
	int			*sprite_order;
	int			bmp;
	int			grid_parsed;
	int			textures_parsed;
	int			bmp_w;
	int			bmp_h;
}				t_map;

typedef struct	s_mother
{
	t_mlx		mlx;
	t_mlx		mlx2;
	t_ray		ray;
	t_player	player;
	t_map		map;
}				t_mother;

void			parse(t_map *newmap, int fd);
void			set_resolution(t_map *newmap, char **res);
void			set_floor_ceiling(t_map *newmap, char **rgb, char cf);
void			set_grid(t_map *newmap, char *line);
void			valid_input_check(int argc, char **argv, t_map *map);
void			check_valid_file(char *file);
char			*correct_rgb_values(char **rgb);
char			*concat_rgb(char **rgb, int k);
void			check_valid_grid(char **grid);
void			flood_fill(t_map *map, t_player *player);
void			flood_fill_check(int x, int y, char **grid, int height);
void			check_resolution(t_mother *mother, t_map *map, t_mlx *mlx);
void			set_map_specs_second(t_map *new_map, char *line,
									char **seperated_line);
void			add_grid_line(t_map *new_map, char *line);
void			set_tex_path(char *parameter, char *line,
							t_map *map, t_texture *tex);
int				check_res_params(char **res);
void			assign_cf_colors(t_map *map, char **color_ints, char cf);

void			sprites(t_map *map, t_player *player, t_ray *ray, t_mlx *mlx);
void			set_sprite_values(t_map *map);
void			count_sprites(t_map *map);
void			load_sprite(t_texture *sprite, void *mlx);
void			init_sprites(t_map *map);
void			swap(int *a, int *b);
void			order_sprites(int *spriteorder,
								int *spritedistance, t_map *map);
void			sprite_draw_data(t_map *map, t_ray *ray);
void			draw_sprite(t_map *map, t_ray *ray, t_mlx *mlx);
void			calc_sprite(t_map *map, t_player *player,
							t_sprite sprite, t_ray *ray);

void			draw(t_mother *new_game, t_mlx *mlx, t_mlx *mlx2);
int				render(t_mother *new_game);
void			draw_ray(t_ray *ray, t_map *map, t_mlx *mlx);
void			calculate_draw_data(t_ray *ray, t_player *player, int height);
void			send_ray(t_ray *ray, char **grid);
void			set_distance_to_sides(t_player *player, t_ray *ray);
void			init_ray(t_ray *ray, t_player *player, t_map *map);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void			d_d_a(t_ray *ray, t_player *player, t_map *map, t_mlx *mlx);

void			rotate_grid(t_map *map);
void			initialize(t_player *player, t_ray *ray, char **grid);
void			set_start_value_ray(int x, int y, t_ray *ray, char **grid);
void			set_start_value_player(int x, int y, t_player
										*player, char **grid);

int				key_press_hook(int keycode, t_mother *new_game);
int				key_release_hook(int keycode, t_mother *new_game);
int				move(t_ray *ray, t_player *player, char **grid);
void			walk(t_ray *ray, t_player *player, char **grid);
void			rotate(t_player *player, t_ray *ray);
void			strafe(t_ray *ray, t_player *player, char **grid);

void			load_textures(t_mlx *mlx_struct, t_map *map, void *mlx);
unsigned	int	texture_picker(t_ray *ray, t_map *map);
unsigned	int	retrieve_texture_pixel(t_texture *texture, int x, int y);

void			save_bmp(t_map *map, t_mlx *mlx);
void			write_bmp_infoheader(t_map *map);
void			write_bmp_header(t_map *map);

void			put_error(char *error);
void			free_stuff(t_map *map);
int				close_window(t_mother *new_game);
void			free_seperated_line(char **seperated_line);

long			ft_atoi_long(const char *str);

#endif
