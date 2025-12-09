/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:17:05 by kedemiro          #+#    #+#             */
/*   Updated: 2025/12/08 23:22:30 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_list	*new_node(char *line, t_data *data)
{
	t_list	*node;
	char	*tmp;

	node = malloc(sizeof(t_list));
	if (!node)
		print_error("Map file can not be read", data);
	tmp = ft_strtrim(line, "\n");
	node->line = tmp;
	node->len = ft_strlen(tmp);
	node->next = NULL;
	return (node);
}
