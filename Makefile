# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 11:42:59 by rjobert           #+#    #+#              #
#    Updated: 2023/11/29 11:43:02 by rjobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC := cc
FLAGS := -Wall -Wextra -Werror
HEADER = ./include/cub3d.h
INC = -I ./include/
GRAPH_COMPILE = -Imlx
GRAPH_LINKING = -L. -lmlx -framework OpenGL -framework Appkit

SRC = main.c events/hooks.c events/moves.c rendering/raycasting.c \
 rendering/render.c rendering/2d.c rendering/texture_mapping.c \
 rendering/init_render.c rendering/load_assets.c player/player.c map/aux_maps.c \
 map/check_lines.c map/check_parameters.c map/get_next_line.c map/map.c \
 map/read_map.c premap/aux_color.c premap/color.c premap/init_textures.c \
 premap/read_textures.c map/get_next_line2.c map/launch_and_free.c \
 premap/free_colors.c clean/exit_clean.c premap/read_textures2.c

OBJS_DIR = ./objs/
SRC_PATH = src/
SRCS = $(addprefix $(SRC_PATH), $(SRC)) 
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))
DEPS = $(addprefix $(OBJS_DIR), $(SRC:.c=.d))

MLX_PATH = ./minilibx
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)/$(MLX_NAME)
LIBFT_PATH = ./libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)/$(LIBFT_NAME)

NAME = cub3D

all: $(MLX) $(LIBFT) $(OBJS_DIR) $(NAME) 

$(MLX):
	@echo "Building MiniLibX"
	@make -sC $(MLX_PATH) all
	@cp $(MLX) . 

$(LIBFT):
	@echo "Building Libft"
	@make -sC $(LIBFT_PATH) all
	@cp $(LIBFT) . 

-include $(DEPS)
$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(GRAPH_LINKING) $(LIBFT_NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/events
	mkdir -p $(OBJS_DIR)/rendering
	mkdir -p $(OBJS_DIR)/player
	mkdir -p $(OBJS_DIR)/map
	mkdir -p $(OBJS_DIR)/premap
	mkdir -p $(OBJS_DIR)/clean

$(OBJS_DIR)%.o: $(SRC_PATH)%.c Makefile $(HEADER)
	$(CC) $(FLAGS) $(GRAPH_COMPILE) $(INC) -c $< -o $@

clean:
	make -C $(MLX_PATH) clean
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -rf $(NAME) $(MLX_NAME) $(LIBFT_NAME)

re: fclean all

.phony: re all fclean clean