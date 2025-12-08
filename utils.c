/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:17:21 by kedemiro          #+#    #+#             */
/*   Updated: 2025/12/08 17:17:22 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	all_free(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	print_error(char *err_msg, t_data *data)
{
	clean_data(data);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}
