#include "libft.h"
#include "minishell.h"

static void	skip_spaces(t_list **list)
{
	t_list	*tmp;

	while (*list && !ft_strcmp(get_str(*list), " "))
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

void		ft_delspaces(t_list **list)
{
	int		flag;
	t_list *prev;
	t_list *curr;

	skip_spaces(list);
	flag = 0;
	prev = NULL;
	curr = *list;
	while (curr)
	{
		if ((!prev || is_redirect(get_str(prev))) &&
			!ft_strcmp(get_str(curr), "echo"))
			flag = 1;
		if (curr && is_redirect(get_str(curr)))
			flag = 0;
		if (curr && !ft_strcmp(get_str(curr), " ") && (!flag || (!ft_strcmp(get_str(prev), "echo") || !ft_strcmp(get_str(prev), "-n"))))
		{
			prev->next = curr->next;
			free(curr);
			curr = prev->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}