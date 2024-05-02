# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 16:26:31 by ilorenzo          #+#    #+#              #
#    Updated: 2024/04/30 16:26:32 by ilorenzo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LIB_FLAGS = -lreadline 


HEADER = ./header/minishell.h

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_HEADER = $(LIBFT_DIR)

SRCS_DIR = srcs/
OBJS_DIR = objs/

SRCS_LS = main.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LS))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LS:.c=.o))

GRAY = \033[2;29m
GREEN = \033[0;32m
NC = \033[0m

all: $(NAME)

#MINISHELL
$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS) $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) -o $@
	@echo "$(GRAY)$(shell printf '%*s' $(shell tput cols) | tr ' ' '-')$(NC)"
	@echo "$(GRAY)$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) -o $@ $(NC)"
	@echo "$(GREEN)$(NAME) compiled succesfully$(NC)"

#OBJS
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER) Makefile
	@$(CC) -c $(CFLAGS) $<  -o $@ 
	@echo "$(GRAY)$(CC) -c $(CFLAGS) $< -o $@ $(NC)"

$(OBJS_DIR):
	@mkdir $@

#LIBFT
$(LIBFT):
	@make -s -C $(LIBFT_DIR)

#CLEAN
clean:
	@make -s -C $(LIBFT_DIR) clean
	@echo "$(GREEN)All objects  removed $(NC)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(GREEN)All binaries removed\n$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re