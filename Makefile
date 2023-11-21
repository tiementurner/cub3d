# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tblanker <tblanker@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/13 14:27:35 by tblanker      #+#    #+#                  #
#    Updated: 2020/10/12 16:59:34 by tblanker      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC_FLAGS = -Wall -Werror -Wextra

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CC_FLAGS += -D LINUX -O2
    CCL_FLAGS += -lXext -lX11 -lm
    MINILIBX = libmlx.a
    MINILIBX_D = minilibx-linux
endif
ifeq ($(UNAME_S),Darwin)
    CC_FLAGS += -D OSX -O2
    CCL_FLAGS += -framework AppKit -framework OpenGL
    MINILIBX = libmlx.dylib
    MINILIBX_D = minilibx-mac
endif

NAME = cub3D

CC = clang

FILES = main.c parse.c get_next_line/get_next_line.c init.c move.c\
		get_next_line/get_next_line_utils.c calculate_ray.c draw.c \
		texture_processing.c texture_loader.c init_sprites.c \
		sprite_processing.c pixel_functions.c input_check.c error.c \
		utils.c bmp.c ft_atoi_long.c utils_2.c utils_3.c keyhandling.c \

OFILES = $(FILES:.c=.o)

LIBS			=	-L libft -lft

all: $(NAME)

$(NAME): $(OFILES) $(MINILIBX)
	$(MAKE) -C libft
	$(CC) $(CCL_FLAGS) $(FILES) -Llibft -lft $(MINILIBX) -o $(NAME)

%.o: %.c
	$(CC) $(CC_FLAGS) -Ilft  -o $@ -c $<

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_D)
	@mv $(MINILIBX_D)/$(MINILIBX) .

clean:
	rm -rf $(OFILES) $(MINILIBX)
	$(MAKE) clean -C libft
	$(MAKE) clean -C $(MINILIBX_D)

fclean: clean
	rm -rf $(NAME)
	rm -rf libft/libft.a

re: fclean all
