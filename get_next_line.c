/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:28:50 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/15 17:17:14 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


// 
char	*get_next_line(int fd)
{
	static t_list	*hold;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0)) // verify the parameters (fd doesnt exist or buffer_size is zero there is no reason to get into the function) and the readability of the fd (testing to read 0 bytes so it does not  avance in the characters) 
		return (NULL);
	line = NULL;
	to_read(fd, &hold)

	return (line);
}


// function to read nbytes into the buffer pointer by "NAME", 
// checking if read() fails (return -1) and return the number of bytes actually read
// or zero (upon reading end-of-file). It would read in the fd until \n or \0 and
// add the nbytes (from buffer pointer by "NAME") to 'hold'.

void	to_read(int fd, t_list **hold)
{
	char	*buffer;
	ssize_t	bytes_read;

	bytes_read = 1; // inicialize the variable with 1 because bytes_read = 0 means that is the end of the fd
	while (bytes_read && !to_search_newline(*hold))
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1) // allocates memory for reading BUFFER_SIZE bytes into the 'buffer' pointer
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE); 
		if (bytes_read <= 0 && *hold == NULL) // checkk if the linked list is empty and there is not more to read or an error has occured on the read()
		{
			buffer == NULL;
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0'; // add null-character to terminate the string
		to_add_on_hold(hold, buffer, bytes_read);
	}
}

// adds the content of our buffer to the end of our hold
void	to_add_on_hold()
{


}
