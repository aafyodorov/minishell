SHELL = /bin/sh

B&W = \033[0;0m
RED =  \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
# FLAGS = -Wall -Werror -Wextra -ggdb
FLAGS = -ggdb
AR = ar rs
RM = rm -rf

LIBFT = libft.a
LIBFTDIR = ./libft/
LIBFTHEADERDIR = ./libft/includes/

NAME = libminishell.a
HEADER = minishell.h
HEADERDIR = ./

SRC = minishell.c\
	  free.c\
	  check.c

SRCDIR = ./

OBJS = $(SRC:.c=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@cp $(LIBFTDIR)$(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(PURPLE)  Library $(NAME) created  $(B&W)"

-include $(DEP)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@$(CC) -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -MMD -c $< -o $@ $(FLAGS)
	@echo "$(GREEN)  Object file $(PURPLE)$@ $(GREEN)created  $(B&W)"

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

test: $(NAME)
	gcc main.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -L./ -lminishell -o $@ -g

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR)

fclean:
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR) $(NAME) ./tests
	@echo "$(RED)  Library $(NAME) deleted  $(B&W)"

re: fclean all

.PHONY: all bonus clean fclean re test
