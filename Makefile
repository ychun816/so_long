# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yilin <yilin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 12:11:58 by yilin             #+#    #+#              #
#    Updated: 2024/07/29 16:27:40 by yilin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

# **************************************************************************** #
#                                 MAIN                                         #
# **************************************************************************** #

NAME = so_long
HEADER = includes/so_long.h
INCL = includes

# **************************************************************************** #
#                               DIRECTORIES                                    #
# **************************************************************************** #

LIBFT_DIR = libft
LIBFT_HEADERS = $(LIBFT_DIR)/includes
LIBFT_A = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx_linux
MLX_A = $(MLX_DIR)/libmlx_Linux.a

SRCS_DIR = srcs/
OBJS_DEPS_DIR = objs_deps/

# **************************************************************************** #
#                         SRCS, OBJS, DEPENTDENCIES                            #
# **************************************************************************** #

SO_LONG_SRCS = so_long
#commands/cmd_push\
		 		 commands/cmd_rotate\
				 commands/cmd_rrotate\
				 commaINCLnds/cmd_swap\
				 stack_operations/avs_to_stack_a\
				 stack_operations/check_error\
				 stack_operations/cleanup_function\
				 stack_operations/push_swap\
				 stack_operations/stack_helper\
				 sort/check_cheap_a2b\
				 sort/check_cheap_b2a\
				 sort/sort_stack_big\
				 sort/sort_stack_small\
				 sort/target_helper

SO_LONG_FILES = $(addsuffix .c, $(SO_LONG_SRCS))
SRCS = $(addprefix $(SRCS_DIR), $(SO_LONG_FILES))
OBJS = $(addprefix $(OBJS_DEPS_DIR), $(SO_LONG_FILES:.c=.o))
DEPS = $(addprefix $(OBJS_DEPS_DIR), $(SO_LONG_FILES:.c=.d))

# **************************************************************************** #
#                            COMPILER & FLAGS                                  #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_HEADERS) -I$(MLX_DIR) -I$(INCL) -g3
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm #-lmlx_Linux
RM = rm -rf
#AR = ar rcs
OBJS_FLAGS = .cache_exists
NORM_FLAGS =	-R CheckForbiddenSourceHeader -R CheckDefine

# **************************************************************************** #
#                             BUILD COMMANDS                                   #
# **************************************************************************** #

all: $(NAME)
	@echo "$(ROSEB)🦄COMPILATION DONE! [$(NAME)] CREATED🦄$(COLOR_RESET)"

$(OBJS_DEPS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER) #| $(OBJS_DEPS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREENB)---COMPILING $< TO $@---$(COLOR_RESET)"

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
# @make -sC $(LIBFT_DIR)
# @make -sC $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	@echo "$(GREENB)---LINKING---$(NAME)$(COLOR_RESET)"

$(LIBFT_A):
	@make -sC $(LIBFT_DIR)
	@echo "$(ORANGE_BBG) $(LIBFT_DIR) CREATED$(COLOR_RESET)"

$(MLX_A):
	@make -sC $(MLX_DIR)
	@echo "$(ORANGE_BBG)$(MLX_DIR) CREATED$(COLOR_RESET)"
#--silent: add at the back if dont want it displayed!

# **************************************************************************** #
#                             CLEAN COMMANDS                                   #
# **************************************************************************** #

norm:
	@make norm -C $(LIBFT_DIR)
	@norminette $(NORM_FLAGS)$(SRCS)$(INCL)

clean:
	@$(RM) $(OBJS_DEPS_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "$(BABEBLUEB)🫧CLEAN DONE! OBJS & DEPS of [$(NAME)] REMOVED🫧$(COLOR_RESET)"

fclean: clean
	@$(RM) $(NAME)
	@rm -f $(LIBFT_A)
	@rm -f $(MLX_A)
	@echo "$(BABEBLUEB)🫧🫧FCLEAN DONE! [$(LIBFT_A)] REMOVED🫧🫧$(COLOR_RESET)"
	@echo "$(BABEBLUEB)🫧🫧FCLEAN DONE! [$(NAME)] REMOVED🫧🫧$(COLOR_RESET)"

re: fclean all
	@echo "$(REDB)RE DONE$(COLOR_RESET)"

-include $(DEPS)

# **************************************************************************** #
#                             PHONY COMMANDS                                   #
# **************************************************************************** #

.PHONY: all clean fclean re
