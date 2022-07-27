/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:24:08 by hyeyukim          #+#    #+#             */
/*   Updated: 2022/07/27 22:30:29 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FT_NULL (void *) 0

typedef struct s_list
{
	int				fd;
	char			buff[BUFFER_SIZE];
	ssize_t			rbytes;
	size_t			offset;
	size_t			new_len;
	size_t			len;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		read_buffer_size(t_list **head, t_list *cur, char *res);
char	*append_line(t_list **head, t_list *cur, char **res, int option);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_list	*create_node(int fd);
int		find_node(t_list **head, t_list **cur, int fd);
int		process_error(t_list **head, t_list *cur, char *str);

#endif