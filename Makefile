SHELL = /bin/sh

B&W = \033[0;0m
RED =  \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
# FLAGS = -Wall -Werror -Wextra -ggdb
FLAGS = -g
AR = ar rs
RM = rm -rf

LIBFT = libft.a
LIBFTDIR = ./libft/
LIBFTHEADERDIR = ./libft/includes/

NAME = libminishell.a
HEADER = minishell.h
HEADERDIR = ./includes/

SRCS = free.c\
	  check.c\
	  ft_cd.c\
	  ft_pwd.c\
	  ft_env.c\
	  ft_echo.c\
	  ft_exit.c\
	  ft_unset.c\
	  ft_export.c\
	  utils.c\
	  utils_2.c\
	  parser.c\
	  delimiters_1.c\
	  delimiters_2.c\
	  parser_utils.c\
	  execve.c\
	  signal.c\
	  fd.c\
	  flags_parser.c\
	  ft_lstreverse.c\
	  parser_del_spaces.c\
	  variables.c\
	  variables_2.c\
	  arr_buf.c\
	  redirect.c
SRCDIR = ./srcs/
SRC = $(addprefix $(SRCDIR), $(SRCS))

OBJS = $(SRCS:.c=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

DEP = $(OBJ:.o=.d)

MINISHELL = minishell
MAIN = $(SRCDIR)main.c

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(MAIN)
	cp $(LIBFTDIR)$(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJ)
#	@echo "$(PURPLE)  Library $(NAME) created  $(B&W)"
	@gcc $(MAIN) -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -L./ -lminishell -o $(MINISHELL) -g
	@echo "$(PURPLE)  Minishell created  $(B&W)"

-include $(DEP)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@$(CC) -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -MMD -c $< -o $@ $(FLAGS)
	@echo "$(GREEN)  Object file $(PURPLE)$@ $(GREEN)created  $(B&W)"

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR) $(NAME)

fclean:
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR) $(NAME) ./tests test
	@echo "$(RED)  Library $(NAME) deleted  $(B&W)"

re: fclean all

.PHONY: all bonus clean fclean re test
