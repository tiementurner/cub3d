/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:50:58 by tblanker       #+#    #+#                */
/*   Updated: 2020/03/13 15:50:13 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "get_next_line/get_next_line.h"

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef	struct		map_struct
{
	int				resolution[2];
	char			*north;
	char			*west;
	char			*east;
	char			*south;
	int				floor_color[3];
	int				ceiling_color[3];
	char			**map_info
}					map;

void	parse(map *newmap, int fd);

#endif