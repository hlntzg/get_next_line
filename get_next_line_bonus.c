/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:29:22 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/24 16:48:55 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* ************************************************************************** */
/* the function updates the data storage by removing the line that has just   */
/* been read on getting_line() and return the update storage to get_next_line */
/* ************************************************************************** */
static char	*updating_data_storage(char *data_storage, char *line)
{
	char	*update_data_storage;

	if (!data_storage)
		return (NULL);
	update_data_storage = ft_strdup(data_storage + ft_strlen(line));
	if (!update_data_storage)
		return (ft_free(&data_storage));
	free(data_storage);
	return (update_data_storage);
}

/* ************************************************************************** */
/* the function extracts a complete line (including \n if there is one) from  */
/* the current data storage and return it to get_next_line()				  */
/* ************************************************************************** */
static char	*getting_line(char *data_storage)
{
	char	*line;
	int		i;

	i = 0;
	if (!data_storage || data_storage[0] == '\0')
		return (NULL);
	while (data_storage[i] && data_storage[i] != '\n')
		i++;
	if (data_storage[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (--i >= 0)
		line[i] = data_storage[i];
	return (line);
}

/* ************************************************************************** */
/* the function duplicates the read data to data storage (if it's empty) or   */
/* concatenates the newly read data to the existing data storage			  */
/* ************************************************************************** */
static char	*managing_data_storage(char *data_storage, char *buffer_r)
{
	char	*tmp;

	if (!data_storage)
	{
		data_storage = ft_strdup(buffer_r);
		if (!data_storage)
			return (ft_free(&data_storage));
	}
	else
	{
		tmp = data_storage;
		data_storage = ft_strjoin(tmp, buffer_r);
		if (!data_storage)
			return (ft_free(&tmp));
		free(tmp);
	}
	return (data_storage);
}

/* ************************************************************************** */
/* the function reads from the file descriptor into the buffer and call the   */
/* managing_data_storage() to updates the data storage content				  */
/* ************************************************************************** */
static char	*getting_data_storage(int fd, char *data_storage)
{
	char	buffer_r[BUFFER_SIZE + 1];
	ssize_t	bytes_r;

	bytes_r = 1;
	while (bytes_r > 0)
	{
		bytes_r = read(fd, buffer_r, BUFFER_SIZE);
		if (bytes_r == 0)
			break ;
		if (bytes_r < 0)
			return (ft_free(&data_storage));
		buffer_r[bytes_r] = '\0';
		data_storage = managing_data_storage(data_storage, buffer_r);
		if (!data_storage)
			return (NULL);
		if (ft_strchr(buffer_r, '\n'))
			break ;
	}
	return (data_storage);
}

/* ************************************************************************** */
/* get_next_line() is the main function that manages the overall process of   */
/* reading and returning the complete line from a file descriptor, supporting */
/* multiple file descriptors concurrently once data_storage is an array of    */
/* strings, so the function can manage multiple files at the same time		  */
/* ************************************************************************** */
char	*get_next_line(int fd)
{
	static char	*data_storage[OPEN_MAX] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 || fd > OPEN_MAX)
		return (ft_free(&data_storage[fd]));
	data_storage[fd] = getting_data_storage(fd, data_storage[fd]);
	if (!data_storage[fd])
		return (NULL);
	line = getting_line(data_storage[fd]);
	if (!line)
		return (ft_free(&data_storage[fd]));
	data_storage[fd] = updating_data_storage(data_storage[fd], line);
	if (!data_storage[fd] && line)
	{
		free(line);
		free(data_storage[fd]);
		return (NULL);
	}
	return (line);
}
