/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:50:58 by tblanker      #+#    #+#                 */
/*   Updated: 2020/08/16 15:45:31 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

#define MLX_SYNC_IMAGE_WRITABLE    1
#define MLX_SYNC_WIN_FLUSH_CMD     2
#define MLX_SYNC_WIN_CMD_COMPLETED 3

#define PI 3.14159

# include "mlx.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_mother {
	t_mlx		mlx;
	t_ray		ray;
	t_player	player;
	t_map		map;
}				mother;

typedef struct  s_mlx {
	void		*mlx;
	void		*win;
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}				t_mlx;

typedef	struct	s_ray {
	double		raydir_x;
	double		raydir_y;
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
	int			stepx;
	int			stepy;
	double		perpwalldist;
	int			drawstart;
	int			drawend;
}				t_ray;

typedef struct	s_player {
	double		player_X;
	double		player_Y;
	double		dir_X;
	double		dir_Y;
}				t_player;

typedef	struct	s_map	{
	int			height;
	int			width;
	int			resolution[2];
	char		*north;
	char		*west;
	char		*east;
	char		*south;
	char		*sprite;
	int			floor_color;
	int			ceiling_color;
	char		**grid;
}				t_map;

void	draw(data *newmap);
void	parse(data *newmap, int fd);
void	set_resolution(data *newmap, char **res);
void 	set_floor_color(data *newmap, char *rgb);
void	set_floor_ceiling(data *newmap, char *rgb, char cf);
void	set_grid(data *newmap, char *line);
int 	render(data *mlx);
void	draw_ray(data *mlx, int x);
void 	calculate_ray_length(data *mlx);
void	send_ray(data *mlx);
void	set_distance_to_sides(data *mlx);
void	my_mlx_pixel_put(data *data, int x, int y, int color);
int		print_keycode(int keycode);
int		close_window(int keycode, data *win);
void	set_start_value_player(int x, int y, t_player player);
void	initialize(t_player player, t_ray ray, char **grid);
int		move(int keycode, data *mlx);
void	move_up(data *new_game);
void    move_down(data *new_game);
void    move_right(data *new_game);
void    move_left(data *new_game);

#endif