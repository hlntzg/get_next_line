/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:29:05 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/20 19:31:50 by hutzig           ###   ########.fr       */
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
		return (0); // return 0 meaning that the program has been executed correctment in the case that hold is empty and there is anything to look for
	current = ft_lstlast(hold);
	tmp = current->content; // store the original pointer to content 
	while (*tmp)
	{
		if (*tmp == '\n') // need to dereference the pointer to be able to compare it with '\n'
			return (1);
		tmp++;
	}
	return (0);
}
/* calculating the length of a line in a linked list of strings until a newline character '\n' is encountered */
int	line_size(t_list *hold)
{
	int		length;
	char	*tmp;

	if (!hold)
		return (0);
	length = 0;
	tmp = hold->content; // Use a temporary pointer for iteration to not modify the original content pointer
	while (hold)
	{
		while (*tmp)
		{
			if (*tmp == '\n')
			{
				length++;
				break;
			}
			length++;
			tmp++;
		}
		hold = hold->next; // increment the while loop to count the lenght of line until \n
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
