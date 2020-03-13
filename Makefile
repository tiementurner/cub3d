# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tblanker <tblanker@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/13 14:27:35 by tblanker       #+#    #+#                 #
#    Updated: 2020/03/13 14:39:32 by tblanker      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SUBDIRS = libft

FILES = main.c parse.c get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

ALL : $(NAME)

$(NAME) :
	$(MAKE) -C libft
	gcc $(FILES) -Llibft -lft