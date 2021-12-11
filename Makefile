# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samuel <samuel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 16:36:58 by sbelondr          #+#    #+#              #
#    Updated: 2021/12/11 15:46:30 by sbelondr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = actions.c\
		actions_move.c\
		display.c\
		free.c\
		lst_select.c\
		main.c\
		move_lst.c\
		move_termcat.c\
		signals.c\
		term.c\
		tools.c\
		tty.c\
		manage_arg.c

DIRSRC = srcs

DIROBJ = objs

OBJ = $(SRC:%.c=$(DIROBJ)/%.o)

NAME = ft_select

DEBUG = -g3

TERMCAP = -lreadline -ltinfo

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
TERMCAP = -lncurses
endif

FLAGS = -Wall -Wextra

INCLUDE =  -I./includes -I./libft/includes

MKDIR = mkdir -p

LIBFT = libft

LIB = -L./libft/libs -lft

LINKLIB = linklib

DIRECTORIES = $(DIROBJ)

# Color

RED = \033[31m
GREEN = \033[32m
BLUE = \033[36m
CLOSE = \033[0m

all: $(NAME)

$(DIRECTORIES):
	@$(MKDIR) $(DIRECTORIES)

$(NAME): $(DIRECTORIES) $(LINKLIB) $(LIBFT) $(OBJ)
	@gcc $(FLAGS) -o $(NAME) $(INCLUDE) $(OBJ) $(LIB) $(TERMCAP)
	@echo "$(BLUE)ft_select$(CLOSE): $(GREEN)Ok$(CLOSE)"

$(LINKLIB):
	@make -C $(LIBFT)

$(DIROBJ)/%.o: $(DIRSRC)/%.c
ifeq ($(UNAME_S),Darwin)
	@gcc $(FLAGS) -o $@ -c $<
else
	@gcc $(FLAGS) $(TERMCAP) -o $@ -c $<
endif

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(DIROBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME) $(NAME).dSYM

clean_select:
	@rm -rf $(DIROBJ)
	@rm -rf $(NAME) $(NAME).dSYM

re: fclean all
