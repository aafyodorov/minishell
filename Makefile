SHELL = /bin/sh

B&W = \033[0;0m
RED =  \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = clang
FLAGS = -Wall -Werror -Wextra -g
# FLAGS = -g
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
	  utils_3.c\
	  utils_4.c\
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
	  redirect.c\
	  minishell.c
SRCDIR = ./srcs/
SRC = $(addprefix $(SRCDIR), $(SRCS))

OBJS = $(SRCS:.c=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

DEP = $(OBJ:.o=.d)

MINISHELL = minishell
MAIN = $(SRCDIR)main.c

CRUTCH = $(LIBFTDIR).crutch

all: $(NAME)

$(NAME): $(CRUTCH) $(OBJ) $(MAIN)
	cp $(LIBFTDIR)$(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJ)
	@$(CC) $(MAIN) -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -L./ -lminishell -o $(MINISHELL) $(FLAGS)
	@echo "$(PURPLE)  Minishell created  $(B&W)"

-include $(DEP)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@$(CC) -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -MMD -c $< -o $@ $(FLAGS)
	@echo "$(GREEN)  Object file $(PURPLE)$@ $(GREEN)created  $(B&W)"

$(CRUTCH): $(LIBFTDIR)sources/*.c $(LIBFTDIR)sources_bonus/*.c $(LIBFTDIR)sources_printf/*.c $(LIBFTDIR)includes/*.h
	@$(MAKE) -C $(LIBFTDIR)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR) $(NAME)

fclean:
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR) $(NAME) $(MINISHELL)
	@echo "$(RED)  Library $(NAME) deleted  $(B&W)"

re: fclean all

.PHONY: all bonus clean fclean re test