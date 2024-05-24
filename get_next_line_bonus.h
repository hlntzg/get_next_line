/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:28:19 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/24 15:18:29 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define MAX_FD 1024

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);

/* ************************************************************************** */
/* 						get_next_line_utils functions						  */
/* ************************************************************************** */

size_t	ft_strlen(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_free(char **ptr);

#endif
