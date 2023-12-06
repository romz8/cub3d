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

SRC = main.c events/hooks.c events/moves.c rendering/raycasting.c rendering/render.c
OBJS_DIR = ./objs/
SRC_PATH = src/
SRCS = $(addprefix $(SRC_PATH), $(SRC)) 
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))
DEPS = $(addprefix $(OBJS_DIR), $(SRC:.c=.d))

MLX_PATH = ./minilibx
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)/$(MLX_NAME)

NAME = cub3d

all: $(MLX) $(OBJS_DIR) $(NAME) 

$(MLX):
	@echo "Building MiniLibX"
	@make -sC $(MLX_PATH) all
	@cp $(MLX) . 

-include $(DEPS)
$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(GRAPH_LINKING)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/events
	mkdir -p $(OBJS_DIR)/rendering

$(OBJS_DIR)%.o: $(SRC_PATH)%.c Makefile $(HEADER)
	$(CC) $(FLAGS) $(GRAPH_COMPILE) $(INC) -c $< -o $@

clean:
	make -C $(MLX_PATH) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME) $(MLX_NAME)

re: fclean all

.phony: re all fclean clean