# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yilin <yilin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/18 16:57:59 by yilin             #+#    #+#              #
#    Updated: 2024/08/22 14:27:05 by yilin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 NAME / MAIN                                  #
# **************************************************************************** #

NAME = so_long

# **************************************************************************** #
#                                 DIRECTORIES                                  #
# **************************************************************************** #

INCL_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs

LIBFT_DIR = libft
MLX_DIR = mlx_linux

# **************************************************************************** #
#                              SRC & OBJ FILES                                 #
# **************************************************************************** #

SRCS = $(addprefix $(SRCS_DIR)/, checkers.c  dfs.c cleanup.c  display.c  exit_program.c  helper_functions.c  so_long.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# **************************************************************************** #
#                                 LIBRARY FILES                                #
# **************************************************************************** #

LIBFT_A = $(LIBFT_DIR)/libft.a
MLX_A = $(MLX_DIR)/libmlx.a

# **************************************************************************** #
#                            COMPILER & FLAGS                                  #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -Iincludes -Ilibft/includes -Imlx_linux
LFLAGS = -Llibft -lft -Lmlx_linux -lmlx -lXext -lX11 -lm
RM = rm -rf

# **************************************************************************** #
#                               BUILD COMMANDS                                 #
# **************************************************************************** #

### Build Targets ###
all: $(NAME)
#@echo "$(ROSEB)🦄COMPILATION DONE! [$(NAME)] CREATED🦄$(COLOR_RESET)"

### Create the executable ###
$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	@echo "$(ROSEB)🚀🦄 $(NAME) SUCCESSFULLY COMPILED! 🦄🚀$(COLOR_RESET)"

### Compile object files ###
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREENB)---🔧 COMPILING $< TO $@ 🔧---$(COLOR_RESET)"

### Create object directory ###
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

### Build the libft library ###
$(LIBFT_A):
	@make -C $(LIBFT_DIR)
	@echo "$(ORANGE_BBG) $(LIBFT_DIR) CREATED$(COLOR_RESET)"

### Build the mlx library ###
$(MLX_A):
	@make -C $(MLX_DIR)
	@echo "$(ORANGE_BBG)$(MLX_DIR) CREATED$(COLOR_RESET)"

### Archive Libraries ###
archives: libft mlx
	@mkdir -p archives
	@if [ -f libft/libft.a ]; then cp libft/libft.a archives/; fi
	@cp mlx_linux/libmlx.a archives/
#@if [ -f libft/libft.a ]; then mv libft/libft.a archives/; fi
#@cp minilibx*/*.a archives/

mlx:
	@if [ ! -d minilibx-linux ]; then git clone https://github.com/42Paris/minilibx-linux.git; fi
	@if [ ! -f archives/libmlx_Linux.a ] || [ ! -d archives ]; then make -C ./minilibx-linux all; fi

libft:
	@if [ ! -f archives/libft.a ] || [ ! -d archives ]; then make -C ./libft all; fi

#--silent: add at the back if dont want it displayed!

# **************************************************************************** #
#                             CLEAN COMMANDS                                   #
# **************************************************************************** #

clean:
	@$(RM) $(OBJS_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "$(BABEBLUEB)🧹 CLEAN DONE! OBJS of [$(NAME)] REMOVED 🧹$(COLOR_RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "$(BABEBLUEB)🫧 FCLEAN DONE! [$(LIBFT_A)] AND $(MLX_A) REMOVED 🫧$(COLOR_RESET)"

### Rebuild the project ###
re: fclean all
	@echo "$(REDB)RE DONE$(COLOR_RESET)"

# **************************************************************************** #
#                              PHONY TARGETS                                   #
# **************************************************************************** #

.PHONY: all clean fclean re libft mlx archives

# **************************************************************************** #
#                              COLOR SETTING                                   #
# **************************************************************************** #

COLOR_RESET = \033[0m
PINKB = \033[1;95m
REDB = \033[1;91m
ROSEB = \033[1;38;5;225m
BLUEB = \033[1;34m
BABEBLUEB = \033[1;38;5;153m
GREENB = \033[1;38;5;85m
PURPLEB = \033[1;38;5;55m
GREEN_BBG = \033[1;42m
BLUE_BBG = \033[1;44m
YELLOW_BBG = \033[1;43m
ORANGE_BBG = \033[1;48;5;214m
