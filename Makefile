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

SRC = main.c
OBJS_DIR = objs
SRC_PATH = src
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRC:.c=.o)))
DEPS =$(addprefix $(OBJS_DIR)/, $(notdir $(SRC:.c=.d)))

MLX_PATH = ./minilibx
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)/$(MLX_NAME)

NAME = cub3d

all: $(MLX) $(NAME)

$(MLX):
	@echo "Building MiniLibX"
	@make -sC $(MLX_PATH) all
	@cp $(MLX) . 

-include $(DEPS)
$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(GRAPH_LINKING)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRC_PATH)/%.c Makefile $(HEADER) | $(OBJS_DIR)
	$(CC) $(FLAGS) $(GRAPH_COMPILE) $(INC) -c $< -o $@

clean:
	make -C $(MLX_PATH) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME) $(MLX_NAME)

re: fclean all

.phony: re all fclean clean