# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmubina                                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/16                               #+#    #+#              #
#    Updated: 2026/07/16                              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes -I $(MLX_DIR)/include

# ---- MLX42 (built through its own CMake) ---------------------------------- #
MLX_DIR		= mlx42
MLX_BUILD	= $(MLX_DIR)/build
MLX_LIB		= $(MLX_BUILD)/libmlx42.a

# ---- Sources -------------------------------------------------------------- #
SRC_DIR		= src
OBJ_DIR		= obj
SRCS		= main.c \
			  game/init.c game/hooks.c \
			  render/raycast.c render/render.c render/textures.c \
			  parsing/read_file.c parsing/split_lines.c parsing/parse.c \
			  parsing/parse_config.c parsing/parse_map.c parsing/validate.c \
			  utils/utils.c utils/utils2.c
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# ---- Platform-specific link flags ----------------------------------------- #
UNAME		:= $(shell uname)
ifeq ($(UNAME), Darwin)
	MLX_LINK	= $(MLX_LIB) -framework Cocoa -framework OpenGL -framework IOKit \
				  -L/opt/homebrew/lib -L/usr/local/lib -lglfw
else
	MLX_LINK	= $(MLX_LIB) -ldl -lglfw -pthread -lm
endif

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LINK) -lm -o $(NAME)
	@echo "cub3D built."

# Build MLX42 with CMake only if the static library is missing.
$(MLX_LIB):
	@echo "Building MLX42..."
	@cmake -B $(MLX_BUILD) -S $(MLX_DIR) -DCMAKE_BUILD_TYPE=Release
	@cmake --build $(MLX_BUILD) --parallel

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

# Remove the MLX42 build tree too (full rebuild of everything).
fclean_all: fclean
	rm -rf $(MLX_BUILD)

# No separate bonus binary: bonus features live in the mandatory build.
bonus: all

re: fclean all

.PHONY: all clean fclean fclean_all re bonus
