# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 16:26:31 by ilorenzo          #+#    #+#              #
#    Updated: 2024/05/12 15:22:20 by pde-masc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LIB_FLAGS = -lreadline -lncurses -lft
INCLUDES = -L$(READLINE_DIR) -L$(LIBFT_DIR)

HEADER = ./header/minishell.h

READLINE_URL = http://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz
READLINE_TAR = readline-8.1.tar.gz
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
			lexer.c\
			lexer_utils.c\
			error.c\
			parsing.c\
			parsing_utils.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LS))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LS:.c=.o))

GRAY = \033[2;29m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m


all: $(NAME)

#MINISHELL
$(NAME): $(LIBFT) $(READLINE) $(OBJS_DIR) $(OBJS) $(HEADER) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(INCLUDES) -o $@ $< 

#OBJS
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER) Makefile
	$(CC) -c $(CFLAGS) $<  -o $@ 
$(OBJS_DIR):
	@mkdir $@

#LIBFT
$(LIBFT):
	@echo "$(YELLOW)Compiling Libft$(NC)"
	@make -s -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled succesfully$(NC)"

#READLINE
$(READLINE): $(READLINE_DIR)
	@echo "$(YELLOW)Compiling readline$(NC)"
	@make -s -C $(READLINE_DIR)
	@echo "$(GREEN)readline compiled succesfully$(NC)"

$(READLINE_DIR):
	@echo "$(YELLOW)Downloading readline$(NC)"
	@curl -O $(READLINE_URL)
	@tar -xzvf $(READLINE_TAR)
	@rm $(READLINE_TAR)
	@echo "$(YELLOW)Configuring readline$(NC)"
	@cd $(READLINE_DIR) && ./configure

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
