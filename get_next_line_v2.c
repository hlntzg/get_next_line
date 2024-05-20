/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:28:50 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/20 10:21:45 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static void	read_fd(int fd, t_list **hold);
static void	line_storage(t_list **hold, char *read_buf, int bytes_read);
static void	line_making(t_list *hold, char **line);
static void	recreate_hold(t_list **hold);
static	int	line_size(t_list *hold);
static t_list	*ft_lstlast(t_list *lst);
static int	search_newline(t_list *hold);
static int	ft_strlen(const char *s);
static void	free_list(t_list *hold);

	
// function to read nbytes into the buffer pointer by "NAME", 
// checking if read() fails (return -1) and return the number of bytes actually read
// or zero (upon reading end-of-file). It would read in the fd until \n or \0 and
// add the nbytes (from buffer pointer by "NAME") to 'hold'.

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
		if (bytes_read <= 0 && *hold == NULL) // check if the linked list is empty and there is no more to read or an error has occured on the read()
		{
			read_buf = NULL;
			free(read_buf);
			return ;
		}
		read_buf[bytes_read] = '\0'; // add null-character to terminate the string
		line_storage(hold, read_buf, bytes_read);
		free(read_buf);
	} // append (t_list **hold, char *buf) create new node and storage the string
}

// adds the content of our buffer to the end of our hold
static void	line_storage(t_list **hold, char *read_buf, int bytes_read)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (bytes_read + 1));
	if (!(new_node->content))
		return ;
	new_node->content = read_buf; // assign to content the pointer to read_buf ((or should i copy character by character from read_buf to content with while?))
	if (*hold == NULL)
		*hold = new_node;
	else
	{
		last_node = ft_lstlast(*hold); // function to get_last_node
		last_node->next = new_node;
	}
}

static void	line_making(t_list *hold, char **line)
{
	int	line_size;

	if (!hold)
		return ;
	line_size = line_size(hold);
	*line = malloc(sizeof(char) * (line_size + 1));
	if (!(*line))
		return ;
	while (hold && hold->content)
	{
		if (*hold->content == '\n');
		{
			**line++ == *hold->content;
			break;
		}
		*line++ == *hold->content;
	hold = hold->next;
	}
	**line = '\0';
}

// clean the hold until the \n so only the characters that have not been returned at the end of get_next_line() remain in the static hold
static void	recreate_hold(t_list **hold)
{
	t_list	*new_node;
	t_list	*last_node;
	int		newline_length;

	new_node = malloc(sizeof(t_list));
	if (!new_node || !hold)
		return ;
	new_node->next = NULL;
	last_node = ft_lstlast(*hold); 
	while (*last_node->content && *last_node->content != '\n') // skip the line that have been return until \n
		content = content->next;								// increase the pointer to point to next character (\n)
	if (*last_node->content && *last_node->content == '\n') // if the fd just have one line, is it satisfy with previous while loop?
		content = content->next;
	newline_length = ft_strlen(*last_node->content);
	new_node->content = malloc(sizeof(char) * (newline_length + 1));
	if (!new_node->content)
		return ;
	while (last_node->content)
		*last_node->content++ = *new_node->content++;
	*new_node->content = '\0';
	free_list(*hold);
	*hold = new_node;
}

static	int	line_size(t_list *hold)
{
	int		line_length;

	if (hold == NULL)
		return (NULL);
	while (hold)
	{
		while (*hold->content)
		{
			if (*hold->content == '\n')
			{
				line_length++;
				break;
			}
			line_length++;
		}
		hold = hold->next; // increment the while loop to count the lenght of line until \n
	}
	return (line_length);
}

static t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

static int	search_newline(t_list *hold)
{
	t_list	*current;

	if (!hold)
		return (0);
	current = ft_lstlast(*hold);
	while (*current->content)
	{
		if (*current->content == '\n')
			return (1);
		current = current->next;
	}
	return (0);
}

static int	ft_strlen(const char *s)
{
	int	counter;

	while (s[counter])
		counter++;
	return (counter);
}

static void	free_list(t_list *hold)
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

char	*get_next_line(int fd)
{
	static t_list	*hold;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) // error handling - verify the parameters (fd doesnt exist or buffer_size is zero there is no reason to get into the function) and the readability of the fd (testing to read 0 bytes so it does not  avance in the characters) 
		return (NULL);
	line = NULL;
	read_fd(fd, &hold);
	if (hold == NULL)
		return (NULL);
	line = line_making(hold, &line);
	recreate_hold(&hold);
	free_list(&hold);
	if (*line == '\0')
	{
		free_list(hold);
		hold = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
