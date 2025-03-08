# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 10:11:29 by nkiampav          #+#    #+#              #
#    Updated: 2025/03/05 10:11:33 by nkiampav         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Target name
NAME		= miniRT

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes
MINILIBX_DIR	= minilibx

# Platform detection
UNAME_S := $(shell uname -s)

# MLX Flags and Libraries
ifeq ($(UNAME_S),Linux)
	# Linux
	MLXFLAGS	= -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm
	MLX_COMPILE	= make -C $(MINILIBX_DIR)
else ifeq ($(UNAME_S),Darwin)
	# macOS
	MLXFLAGS	= -L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit
	MLX_COMPILE	= make -C $(MINILIBX_DIR)
else
	# Unsupported platform
	$(error Unsupported operating system)
endif

# Math library
MATHFLAGS	= -lm

# Source files - adjusted to match your actual directory structure
SRC_DIRS	= main parser vector ray render objects scene utils
SRCS		= $(foreach dir,$(SRC_DIRS),$(wildcard $(SRC_DIR)/$(dir)/*.c))
OBJS		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Header files
INCS		= $(wildcard $(INC_DIR)/*.h)

# Libft
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

# Rules
all: $(LIBFT) $(MINILIBX_DIR)/libmlx.a $(NAME)

# Rule to build libft
$(LIBFT):
	@echo "🔨 Compiling libft..."
	@make -C $(LIBFT_DIR)

$(MINILIBX_DIR)/libmlx.a:
	@echo "🔨 Compiling MinilibX..."
	@$(MLX_COMPILE)

$(NAME): $(OBJS)
	@echo "🔨 Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_FLAGS) $(MLXFLAGS) $(MATHFLAGS)
	@echo "✅ Compilation complete!"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MINILIBX_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Clean object files
clean:
	@echo "🧹 Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@if [ -d $(MINILIBX_DIR) ] && [ -f $(MINILIBX_DIR)/Makefile ]; then \
		make -C $(MINILIBX_DIR) clean; \
	fi
	@echo "✅ Object files cleaned!"

# Full clean
fclean: clean
	@echo "🧹 Removing executable..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "✅ Executable removed!"

# Rebuild
re: fclean all

# Bonus target (if needed)
bonus: all

# Phony targets
.PHONY: all clean fclean re bonus

# Helpful information
help:
	@echo "Available targets:"
	@echo "  all     : Build the project"
	@echo "  clean   : Remove object files"
	@echo "  fclean  : Remove object files and executable"
	@echo "  re      : Rebuild the project"
	@echo "  bonus   : Build with bonus features"
