/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:29:05 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/15 17:17:10 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	to_search_newline(t_list *hold)
{
	t_list	*current;
	int		i;

	if (hold == NULL)
		return (0); // returns 0 meaning that the program has been executed correctment in the case that hold is empty and there is anything to look for
	current = ft_lstlast(hold);
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}


t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;
	
	current = lst;
	while (current->next != NULL && current)
		current = current->next;
	return (current);
}
