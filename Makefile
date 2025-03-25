# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 13:05:36 by pjaguin           #+#    #+#              #
#    Updated: 2025/03/25 16:14:54 by fureimu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = ./libft
SRC_DIR = ./srcs/
OBJ_DIR = ./objects/
INC_DIR = ./includes/
UTILS_DIR = ./srcs/utils/
INIT_DIR = ./srcs/init/
BUILTIN_DIR = ./srcs/builtins/

FILES = 		minishell.c lexing.c parsing.c signals.c exit.c env.c exec.c

UTILS_FILES =	boolean_checks.c lex_utils.c lex_utils2.c env_utils.c env_utils2.c exec_utils.c \
				ft_str_substitute.c parse_utils.c 

INIT_FILES =	init_data.c init_exec.c

BUILTIN_FILES = builtins.c cd.c

OBJ =	$(addprefix $(OBJ_DIR), $(FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(UTILS_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(INIT_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(BUILTIN_FILES:.c=.o)) \

CC = cc
MAKE = make
CFLAGS = -Wall -Werror -Wextra -g 
INC_H = -I $(INC_DIR) -I $(LIBFT_DIR)/includes

DEFAULT = \033[0m
DEF_COLOR = \033[0;90m
WHITE = \033[1;37m
GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m

all: $(NAME)

$(NAME) : $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"
	@$(CC) $(CFLAGS) $(INC_H) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME) -l readline

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c $< -o $@

$(OBJ_DIR)%.o: $(INIT_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c $< -o $@
	
$(OBJ_DIR)%.o: $(BUILTIN_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean: 
	@rm -rf $(OBJ)
	@echo "$(GREEN)$(NAME) object files cleaned!$(DEFAULT)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(CYAN)$(NAME) executables and objects removed succesfully!$(DEFAULT)"
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(CYAN)libft executables and objects removed succesfully!$(DEFAULT)"
	
re: fclean all

go: all
	@./$(NAME)
	@rm -rf $(NAME)

gov: all
	@valgrind --suppressions=valgrind-readline.supp --leak-check=full --show-leak-kinds=all ./$(NAME)
	@rm -rf $(NAME)

# Specify that these are not files to compile (just for safety)
.PHONY: all clean fclean re go gov
	