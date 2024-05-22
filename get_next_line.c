/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:09:31 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/22 19:17:32 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*recreate_stash(char **stash, char *line)
{
	char	*tmp;

//	printf("\nstash in recreate_stash: %s", *stash);
	tmp = ft_strdup(*stash + ft_strlen(line));
//	printf("\ntmp in recreate_stash: %s", tmp);
	free(*stash);
	*stash = NULL;
//	printf("\nfreed stash in recreate_stash: %s", *stash);
	*stash = ft_strdup(tmp);
//	printf("\nnew stash in recreate_stash: %s", *stash);
	return (*stash);
}

static char	*getting_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line = malloc(sizeof(char *) * (i + 1));
	if (!line)
		return (NULL);
	line[i + 1] = '\0';
	while (i--)
		line[i] = stash[i];
//	printf("line: %s", line);
	return (line);
}

static char	*read_and_store(int fd, char **stash)
{
	char	buffer_r[BUFFER_SIZE + 1];
	ssize_t	bytes_r;
	char	*tmp;

	bytes_r = 1;
	while (bytes_r != 0)
	{
		bytes_r = read(fd, buffer_r, BUFFER_SIZE);
		if (bytes_r <= 0)
			return (NULL);
	//	if (bytes_r == 0)
	//		break ;
		buffer_r[bytes_r] = '\0';
		//printf("\nbuffer_r: %s", buffer_r);
		if (*stash == NULL)
			*stash = ft_strdup("");
		//	printf("stash in read_and_store: -%s-\n", *stash);
		tmp = *stash;
		*stash = ft_strjoin(tmp, buffer_r);
	//	printf("\nstash: %s", *stash);
		if (ft_strchr(buffer_r, '\n'))
			break ;
	}
//	printf("stash newline: %s\n", *stash);
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);	
	stash = read_and_store(fd, &stash);
	if (!stash)
		return (NULL);
//	printf("stash bf line: %s", stash);
	line = getting_line(stash);
//	printf("line gnl: %s\nstash gnl: %s", line, stash);
	if (!line)
	{
		free (stash);
	}
//	printf("stash after line: %s", stash);
	stash = recreate_stash(&stash, line);
//	printf("stash recreated: %s", stash);
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

	fd = open("../_tests/fd_test.txt", O_RDONLY);
	if (fd < 0)
		return (0);
	i = 1;
	line = "1";
	while (line)
	{
		line = get_next_line(fd);
		printf("[%d] - %s", i, line);
		//free(line);
		i++;
	}
	return (0);
}*/
