SRC = open.c \
	  list.c \
	  move.c \
	  sort.c \
	  ft_ls.c \
	  init.c \
	  parcours.c \
	  error.c \
	  parser.c \
	  insert.c \
	  tools_insert.c \
	  permissions.c \
	  gest_time.c \
	  display.c \
	  display_l.c \
	  list_remove.c

DIROBJ = ../../obj

NAME = ft_ls

OBJ = $(SRC:%.c=$(DIROBJ)/%.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[36mft_ls\033[0m Make: \033[32mOk\033[0m"

$(DIROBJ)/%.o: %.c
	@gcc $< $(FLAGS) -c -o $@
	@echo "\033[36mft_ls\033[0m $*: \033[32mOk\033[0m"

clean:
	@rm -f $(OBJ)

fclean: clean

re: fclean $(NAME)

.PHONY: all clean fclean re
.SILENT: all $(NAME) clean fclean re
