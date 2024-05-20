/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:29:20 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/20 13:03:34 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef	BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

# include <unistd.h> // read()
# include <stdlib.h> // malloc()
# include <sys/types.h> // ssize_t

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);

t_list	*ft_lstlast(t_list *lst);
int		ft_strlen(const char *s);
int		search_newline(t_list *hold);
int		line_size(t_list *hold);
void	free_list(t_list *hold);

#endif
