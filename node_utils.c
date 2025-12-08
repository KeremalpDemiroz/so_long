#include "so_long.h"

void	free_node(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		if ((*list)->line)
			free((*list)->line);
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

void	add_back(t_list **list, t_list *new)
{
	t_list	*temp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	count_node(t_data *data)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = data->list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_list	*new_node(char *line, int len, t_data *data)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		print_error("Map file can not be read", data);
	node->line = line;
	node->len = len;
	node->next = NULL;
	return (node);
}
