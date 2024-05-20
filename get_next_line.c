/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:28:50 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/20 19:39:29 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
// adds the content of our buffer to the end of our hold
static void	line_storage(t_list **hold, char *read_buf, int bytes_read)
{
	t_list	*new_node;
	t_list	*last_node;
	int		i;
	
	i = 0;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (bytes_read + 1));
	if (!(new_node->content))
		return ;
	new_node->content = read_buf;  // assign to content the pointer to read_buf ((or should i copy character by character from read_buf to content with while?))
///	printf("kavine line: %s\n", new_node->content);
	if (*hold == NULL)
		*hold = new_node;
	else
	{
		last_node = ft_lstlast(*hold); // function to get_last_node
		last_node->next = new_node;
	}
}

// function to read nbytes into the buffer pointer by "NAME", checking if read() fails (return -1) and return the number of bytes actually read or zero (upon reading end-of-file). It would read in the fd until \n or \0 and add the nbytes (from buffer pointer by "NAME") to 'hold'.
static void	read_fd(int fd, t_list **hold)
{
	char	*read_buf; // variable to stock the string
	ssize_t	bytes_read; 

	bytes_read = 1; // inicialize the variable with 1 because bytes_read = 0 means that is the end of the fd
	while (bytes_read && !search_newline(*hold)) // fetch newline and if there is not, go into the loop -- return true or false
	{
		read_buf = malloc(sizeof(char) * BUFFER_SIZE + 1); // allocates memory for reading BUFFER_SIZE bytes into the 'buffer' pointer
		if (!read_buf)
			return ;
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		//printf("%zu", bytes_read);
		if (bytes_read <= 0 && *hold == NULL) // check if the linked list is empty and there is no more to read or an error has occured on the read()
		{
			free(read_buf);
			//read_buf = NULL;
			return ;
		}
		read_buf[bytes_read] = '\0'; // add null-character to terminate the string
		//printf("%s\n", read_buf);
		line_storage(hold, read_buf, bytes_read);
		free(read_buf);
		//printf("check");
	} // append (t_list **hold, char *buf) create new node and storage the string
}

static void	line_making(t_list *hold, char **line)
{
	char	*tmp;
	
	if (!hold || !line)
		return ;
	*line = malloc(sizeof(char) * (line_size(hold) + 1));
	if (!(*line))
		return ;
	tmp = *line;
	while (hold && hold->content)
	{
		if (*hold->content == '\n')
		{
			*tmp++ = *hold->content++;
			break;
		}
		*tmp++ = *hold->content++;
		hold = hold->next;
	}
	*tmp = '\0';
}

/* clean the hold until the \n so only the characters that have not been returned at the end of get_next_line() remain in the static hold */
static void	recreate_list(t_list **hold)
{
	t_list	*new_node;
	t_list	*last_node;
	char	*src;
	char	*dst;

	new_node = malloc(sizeof(t_list));
	if (!new_node || !hold)
		return ;
	new_node->next = NULL;
	last_node = ft_lstlast(*hold);
//	while (last_node->content)
//	{
//		if (*last_node->content == '\n')
//			break;
//		last_node->content++;
//	}
	while (last_node->content && *last_node->content != '\n') // skip the line that have been return until n
		last_node->content++;								// increase the pointer to point to next character (\n)
	if (last_node->content && *last_node->content == '\n')
		last_node->content++; // Accessing something beyond the \0 when buffer_size fits the \n 
	if (last_node->content)
	{
		new_node->content = malloc(sizeof(char) * (ft_strlen(last_node->content) + 1));
		if (!new_node->content)
		{
		//	free(new_node);
			return ;
		}		
		src = last_node->content;
		dst = new_node->content;
		while (*src)
			*dst++ = *src++;
		*dst = '\0';
	}
	free_list(*hold);
	*hold = new_node;
}

char	*get_next_line(int fd)
{
	static t_list	*hold;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) // error handling - verify the parameters (fd doesnt exist or buffer_size is zero there is no reason to get into the function) and the readability of the fd (testing to read 0 bytes so it does not  avance in the characters) 
		return (NULL);
	line = NULL;
	read_fd(fd, &hold);
	if (!hold)
		return (NULL);
	line_making(hold, &line);
	recreate_list(&hold);
//	free_list(hold);
	if (*line == '\0')
	{
		free_list(hold);
		hold = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

#include <fcntl.h> // open();
#include <stdio.h> // printf();
#include <stdlib.h> // free();

int	main()
{
	int		fd;
	char	*line;
	int		i;

	fd = open("../_tests/fd_test.txt", O_RDONLY); // open fd on the read-open mode (flag)
	if (fd < 0) // check if open() fails or there is not a fd
		return (0);
	i = 1;
	while (i > 0)
	{
		line = get_next_line(fd);
		if (line == NULL) // get_next_line returns NULL when it is the end of the file
			break;
		printf("[%d] - %s", i, line);
		free(line); // it's necessary to free the pointer each time to avoid leaks
		i++;
	}
	return (0);
}
