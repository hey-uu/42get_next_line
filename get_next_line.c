/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:26:36 by hyeyukim          #+#    #+#             */
/*   Updated: 2022/07/27 22:31:14 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_buffer_size(t_list **head, t_list *cur, char *res)
{
	cur->rbytes = read(cur->fd, cur->buff, BUFFER_SIZE);
	if (cur->rbytes < 0)
		return (process_error(head, cur, res));
	cur->offset = 0;
	cur->len = 1;
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*head = FT_NULL;
	t_list			*cur;
	char			*res;

	if (BUFFER_SIZE <= 0 || fd < 0 || !find_node(&head, &cur, fd))
		return (FT_NULL);
	res = FT_NULL;
	while (1)
	{
		if (cur->offset == BUFFER_SIZE)
			if (!read_buffer_size(&head, cur, res))
				return (FT_NULL);
		if (cur->rbytes == 0 || cur->offset == (size_t) cur->rbytes)
			if (!process_error(&head, cur, FT_NULL))
				return (res);
		if (cur->buff[cur->offset] == '\n')
			return (append_line(&head, cur, &res, 1));
		if (cur->offset == (size_t) cur->rbytes - 1)
			if (!append_line(&head, cur, &res, 0))
				return (FT_NULL);
		cur->offset++;
		cur->len++;
	}
}
