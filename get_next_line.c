/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:28:50 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/21 17:22:48 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

static void	line_storage(t_list **hold, char *read_buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = strdup(read_buf);
	if (!(new_node->content))
		return ;
	if (*hold == NULL)
		*hold = new_node;
	else
	{
		last_node = ft_lstlast(*hold);
		last_node->next = new_node;
	//	printf("last node: %s\n", new_node->content);
	}
//	printf("what is in hold at the end of line storage: %s\n", (*hold)->content);
}

static void	line_making(t_list *hold, char **line)
{
	int	i;
	int	j;
	
	j = 0;
	if (!hold)
		return ;
	////printf("line_making: %s", hold->content)
	*line = malloc(sizeof(char) * (line_size(hold) + 1));
	if (!(*line))
		return ;
	while (hold)
	{
		//printf("Line making hold content: %s\n", hold->content);
		i = 0;
		while (hold->content[i])
		{
			if (hold->content[i] == '\n')
			{	
				(*line)[j++] = hold->content[i];
				break ;
			}
			(*line)[j++] = hold->content[i++];
		}
		hold = hold->next;
	}
	(*line)[j] = '\0';
	//printf("line making is: %s\n", *line);
}

static void	recreate_list(t_list **hold)
{
	t_list	*new_node;
	t_list	*last_node;
	size_t	i;

	new_node = malloc(sizeof(t_list));
	if (!new_node || !hold || !*hold)
		return ;
	new_node->next = NULL;
	last_node = ft_lstlast(*hold);
	if (!last_node || !last_node->content)
		return ;
//	while (last_node->content)
//	{
//		if (*last_node->content == '\n')
//			break;
//		last_node->content++;
//	}
	i = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	if (last_node->content[i] && last_node->content[i] == '\n')
		i++; //Access  beyond \0 if buffer_size = \n 
	if (last_node->content[i])
	{
		new_node->content = strdup(last_node->content + i);
		//printf("\nlast node content after newline: %s\n", new_node->content);
		if (!new_node->content)
		{
		//	free(new_node);
			return ;
		}
	}
	free_list(*hold);
	*hold = new_node;
}

static void	read_fd(int fd, t_list **hold)
{
	char	*read_buf;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read && !search_newline(*hold))
	{
		read_buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!read_buf)
			return ;
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
//		printf("bytes_read = %zd\n", bytes_read);
		if (bytes_read <= 0)
		{
//			puts("No hold");
			free(read_buf);
			return ;
		}
		read_buf[bytes_read] = '\0';
//		printf("read_buf: %s\n", read_buf);
		line_storage(hold, read_buf);
		free(read_buf);
	}
}
char	*get_next_line(int fd)
{
	static t_list	*hold;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	read_fd(fd, &hold);
	if (!hold)
	{
//		puts("No hold");
		return (NULL);
	}
	if (hold && hold->content && hold->content[0])
		line_making(hold, &line);
	recreate_list(&hold);
//	free_list(hold);
	if (!line || *line == '\0')
	{
		free_list(hold);
		hold = NULL;
//		puts("Setting hold to NULL");
//		free(line);
		return (NULL);
	}
	return (line);
}
/*
#include <fcntl.h> // open();
#include <stdio.h> // printf();
#include <stdlib.h> // free();

int	main()
{
	int		fd;
	char	*line;
	int		i;

	fd = open("empty_file", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file descriptor");
		return (0);
	}
	i = 1;
	while (i > 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("[%d] - %s\n", i, line);
		free(line);
		i++;
	}
	if (close(fd) < 0)
		printf("Error closing file descriptor");
	return (0);
 }*/
