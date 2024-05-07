# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 16:26:31 by ilorenzo          #+#    #+#              #
#    Updated: 2024/05/04 19:03:53 by pde-masc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LIB_FLAGS = -lreadline -lncurses -lft
INCLUDES = -L$(READLINE_DIR) -L$(LIBFT_DIR)

HEADER = ./header/minishell.h

READLINE_DIR = ./readline-8.1
READLINE = $(READLINE_DIR)/libreadline.a
READLINE_HEADER = $(READLINE_DIR)

HISTORY_DIR = ./readline-8.1
HISTORY = $(HISTORY_DIR)/libhistory.a
HISTORY_HEADER = $(HISTORY_DIR)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_HEADER = $(LIBFT_DIR)

SRCS_DIR = srcs/
OBJS_DIR = objs/

SRCS_LS =	main.c\
			parsing.c\
			lexer.c\
			lexer_utils.c\
			error.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LS))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LS:.c=.o))

GRAY = \033[2;29m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m


all: $(NAME)

#MINISHELL
$(NAME): $(LIBFT) $(READLINE) $(OBJS_DIR) $(OBJS) $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(INCLUDES) -o $@ $< 

#OBJS
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER) Makefile
	@$(CC) -c $(CFLAGS) $<  -o $@ 
$(OBJS_DIR):
	@mkdir $@

#LIBFT
$(LIBFT):
	@echo "$(YELLOW)Compiling Libft$(NC)"
	@make -s -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled succesfully$(NC)"

#READLINE
$(READLINE):
	@echo "$(YELLOW)Compiling readline$(NC)"
	@make -s -C $(READLINE_DIR)
	@echo "$(GREEN)readline compiled succesfully$(NC)"

#CLEAN
clean:
	@make -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)Objects removed$(NC)"
fclean: clean
	@make -s -C $(READLINE_DIR) clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)
	@echo "$(GREEN)Objects and executables removed$(NC)"

re: fclean all

.PHONY: all clean fclean re
