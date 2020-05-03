# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samuel <samuel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 16:36:58 by sbelondr          #+#    #+#              #
#    Updated: 2020/05/03 19:52:26 by samuel           ###   ########.fr        #
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
		tty.c


DIRSRC = srcs

DIROBJ = objs

OBJ = $(SRC:%.c=$(DIROBJ)/%.o)

NAME = ft_select

DEBUG = -g3

TERMCAP = -ltermcap

FLAGS = -Wall -Werror -Wextra

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

all: $(DIRECTORIES) $(LINKLIB) $(NAME)

$(DIRECTORIES):
	@$(MKDIR) $(DIRECTORIES)

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(FLAGS) $(TERMCAP) -o $(NAME) $(INCLUDE) $(DIROBJ)/*o $(LIB)
	@echo "ft_select: Ok"
# @echo "$(BLUE)ft_select$(CLOSE): $(GREEN)Ok$(CLOSE)"

$(LINKLIB):
	@make -C $(LIBFT)

$(DIROBJ)/%.o: $(DIRSRC)/%.c
	@gcc -o $@ $(FLAGS) -c $<

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(DIROBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME) $(NAME).dSYM

re: fclean all

