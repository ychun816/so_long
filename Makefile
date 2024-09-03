# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yilin <yilin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/18 16:57:59 by yilin             #+#    #+#              #
#    Updated: 2024/08/28 18:54:17 by yilin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                                 NAME / MAIN                                  #
# **************************************************************************** #

NAME = so_long
NAMEB = so_long_bonus

# **************************************************************************** #
#                                 DIRECTORIES                                  #
# **************************************************************************** #

INCL_DIR = includes
SRCS_DIR = srcs
SRCSB_DIR = srcs_bonus
OBJS_DIR = objs
OBJSB_DIR = objs_bonus

LIBFT_DIR = libft
MLX_DIR = mlx_linux

# **************************************************************************** #
#                              SRC & OBJ FILES                                 #
# **************************************************************************** #

SRCS = $(addprefix $(SRCS_DIR)/, check_display.c check_map.c check_helpers.c cleanup.c \
	dfs.c display.c exit_program.c helper_functions.c move_player.c so_long.c track_moves.c)
SRCSB = $(addprefix $(SRCSB_DIR)/, check_display_bonus.c check_map_bonus.c dfs_bonus.c \
	exit_program_bonus.c move_player_bonus.c track_moves_bonus.c check_helpers_bonus.c \
	cleanup_bonus.c display_bonus.c helper_functions_bonus.c so_long_bonus.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
OBJSB = $(SRCSB:$(SRCSB_DIR)/%.c=$(OBJSB_DIR)/%.o)

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
all: mlx $(NAME)

### NAME Create the executable ###
$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	@echo "$(ROSEB)🚀🦄 $(NAME) SUCCESSFULLY COMPILED! 🦄🚀$(COLOR_RESET)"

### BONUS: NAME ###
$(NAMEB): $(OBJSB) $(LIBFT_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJSB) $(LFLAGS) -o $(NAMEB)
	@echo "$(ROSEB)🚀🦄 $(NAMEB) SUCCESSFULLY COMPILED! 🦄🚀$(COLOR_RESET)"

bonus: mlx $(NAMEB)

### Compile object files ###
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREENB)---🔧 COMPILING $< TO $@ 🔧---$(COLOR_RESET)"

### BONUS: Compile object files ###
$(OBJSB_DIR)/%.o: $(SRCSB_DIR)/%.c | $(OBJSB_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREENB)---🔧 COMPILING $< TO $@ 🔧---$(COLOR_RESET)"

### Create object directory ###
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

### BONUS: Create object directory ###
$(OBJSB_DIR):
	@mkdir -p $(OBJSB_DIR)

### Build the libft library ###
$(LIBFT_A):
	@make -C $(LIBFT_DIR)
	@echo "$(ORANGE_BBG) $(LIBFT_DIR) CREATED$(COLOR_RESET)"

### Build the mlx library ###
$(MLX_A): mlx
	@make -C $(MLX_DIR)
	@echo "$(ORANGE_BBG)$(MLX_DIR) CREATED$(COLOR_RESET)"

### Ensure mlx_linux exists ###
mlx:
	@if [ ! -d $(MLX_DIR) ]; then \
	echo "$(REDB)Directory $(MLX_DIR) does not exist. Cloning...$(COLOR_RESET)"; \
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	echo "$(REDB)MLX cloned into [$(MLX_DIR)]$(COLOR_RESET)"; \
	fi

### Archive Libraries ###
archives: libft mlx
	@mkdir -p archives
	@if [ -f $(LIBFT_A) ]; then cp $(LIBFT_A) archives/; fi
	@cp $(MLX_A) archives/

#--silent: add at the back if don't want it displayed!

### Clean up object files and directories ###
clean:
	@$(RM) $(OBJS_DIR)
	@$(RM) $(OBJSB_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "$(BABEBLUEB)🧹 CLEAN DONE! OBJS of [$(NAME)] REMOVED 🧹$(COLOR_RESET)"

### Remove all built files ###
fclean: clean
	@$(RM) $(NAME) $(NAMEB)
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@$(RM) $(MLX_DIR)
	@echo "$(BABEBLUEB)🫧 FCLEAN DONE! [$(LIBFT_A)] / [$(MLX_A)] / [$(MLX_DIR)] REMOVED 🫧$(COLOR_RESET)"

### Rebuild the project ###
re: fclean all
	@echo "$(REDB)RE DONE$(COLOR_RESET)"

# **************************************************************************** #
#                              PHONY TARGETS                                   #
# **************************************************************************** #

.PHONY: all clean fclean re libft mlx archives bonus

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
