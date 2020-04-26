# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 16:36:58 by sbelondr          #+#    #+#              #
#    Updated: 2020/04/26 18:30:28 by sbelondr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = display.c\
			free.c\
			lst_select.c\
			main.c\
			move_lst.c\
			move_termcat.c\
			term.c\
			tty.c


DIRSRC = srcs

DIROBJ = objs

OBJ = $(SRC:%.c=$(DIROBJ)/%.o)

NAME = ft_select

EXEC = ft_select

DEBUG = -g3

FLAGS = -Wall -Wextra $(DEBUG)

MKDIR = mkdir -p

LIBFT = libft

LINKLIB = linklib

DIRECTORIES = $(DIROBJ)

all: $(DIRECTORIES) $(LINKLIB) $(NAME)

$(DIRECTORIES):
	@$(MKDIR) $(DIRECTORIES)

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(FLAGS) $(DIROBJ)/*o -L./libft/libs -lft -lncurses -o $(EXEC)
	@echo "\033[36mft_select\033[0m gcc: \033[32mOk\033[0m"

$(LINKLIB):
	@make -C $(LIBFT)

$(DIROBJ)/%.o: $(DIRSRC)/%.c
	@gcc -o $@ $(FLAGS) -c $<
	@echo "\033[36mft_select\033[0m $*: \033[32mOk\033[0m"

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(DIROBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -rf $(EXEC) $(EXEC).dSYM

re: fclean all

