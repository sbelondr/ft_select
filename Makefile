# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samuel <samuel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 16:36:58 by sbelondr          #+#    #+#              #
#    Updated: 2020/04/30 12:29:51 by samuel           ###   ########.fr        #
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

EXEC = ft_select

DEBUG = -g3

CURSE = -lncurses

TERMCAP = -ltermcap

FLAGS = -Wall -Werror -Wextra

MKDIR = mkdir -p

LIBFT = libft

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
	@gcc $(FLAGS) $(DIROBJ)/*o -L./libft/libs -lft $(CURSE) -o $(EXEC)
	@echo "ft_select: Ok"
	#@echo "$(BLUE)ft_select$(CLOSE): $(GREEN)Ok$(CLOSE)"

$(LINKLIB):
	@make -C $(LIBFT)

$(DIROBJ)/%.o: $(DIRSRC)/%.c
	@gcc -o $@ $(FLAGS) -c $<
#	@echo "$(BLUE)$*$(CLOSE): $(GREEN)Ok$(CLOSE)\n"
#	@echo "\033[36mft_select\033[0m $*: \033[32mOk\033[0m"

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(DIROBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -rf $(EXEC) $(EXEC).dSYM

re: fclean all

