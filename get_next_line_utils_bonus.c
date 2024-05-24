/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:28:37 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/24 13:37:46 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*str_copy;
	int		i;

	i = 0;
	str_copy = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str_copy)
		return (NULL);
	while (s1[i])
	{
		str_copy[i] = s1[i];
		i++;
	}
	str_copy[i] = '\0';
	return (str_copy);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		join[j++] = s1[i++];
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}

char	*ft_strchr(char *s, int c)
{
	char	convert_c;

	convert_c = (char) c;
	while (1)
	{
		if (*s == convert_c)
			return ((char *) s);
		else if (*s == '\0')
			break ;
		s++;
	}
	return (NULL);
}

char	*ft_free(char **ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}
