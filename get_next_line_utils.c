/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:29:05 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/21 15:48:12 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	ft_strlen(const char *s)
{
	int	counter;

	counter = 0;
	while (*s)
	{
		s++;
		counter++;
	}
	return (counter);
}

int	search_newline(t_list *hold)
{
	t_list	*current;
	char	*tmp;

	if (!hold)
		return (0);
	current = ft_lstlast(hold);
	tmp = current->content;
	if (!tmp)
		return (0);
	while (*tmp)
	{
		if (*tmp == '\n')
			return (1);
		tmp++;
	}
	return (0);
}

int	line_size(t_list *hold)
{
	int		length;

	if (!hold)
		return (0);
	length = 0;
	while (hold)
	{
		length += ft_strlen(hold->content);
		hold = hold->next;
	}
	return (length);
}

void	free_list(t_list *hold)
{
	t_list	*current;
	t_list	*next;

	if (!hold)
		return ;
	current = hold;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
