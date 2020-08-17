# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tblanker <tblanker@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/13 14:27:35 by tblanker      #+#    #+#                  #
#    Updated: 2020/06/17 13:11:28 by tblanker      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC_FLAGS = -Wall -Werror -Wextra

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CC_FLAGS += -D LINUX
    CCL_FLAGS += -lXext -lX11 -lm
    MINILIBX = libmlx.a
    MINILIBX_D = minilibx-linux
endif
ifeq ($(UNAME_S),Darwin)
    CC_FLAGS += -D OSX
    CCL_FLAGS += -framework AppKit -framework OpenGL
    MINILIBX = libmlx.dylib
    MINILIBX_D = minilibx-mac
endif

NAME = cub3d

CC = clang

SUBDIRS = libft

FILES = main.c parse.c get_next_line/get_next_line.c init.c move.c\
		get_next_line/get_next_line_utils.c calculate_ray.c draw.c

OFILES = $(FILES:.c=.o)

LIBS			=	-L libft -lft

ALL : $(NAME)

$(NAME) : $(OFILES) $(MINILIBX)
	$(MAKE) -C libft
	$(CC) $(CCL_FLAGS) $(FILES) -Llibft -lft $(MINILIBX) -o $(NAME)

%.o : %.c
	$(CC) $(CC_FLAGS) -Ilft $< -o $@

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_D)
	@mv $(MINILIBX_D)/$(MINILIBX) .
	@mv $(MINILIBX_D)/mlx.h .

clean :
	rm -rf $(OFILES)
	$(MAKE) clean -C libft
	$(MAKE) clean -C mlx