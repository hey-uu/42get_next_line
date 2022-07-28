/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:56:23 by hyeyukim          #+#    #+#             */
/*   Updated: 2022/07/28 10:01:36 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*create_node(int fd)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (FT_NULL);
	new->fd = fd;
	new->rbytes = BUFFER_SIZE;
	new->offset = BUFFER_SIZE;
	new->new_len = 0;
	new->len = 1;
	new->next = FT_NULL;
	return (new);
}

int	find_node(t_list **head, t_list **cur, int fd)
{
	t_list	*tem;

	if (!*head)
	{
		*head = create_node(fd);
		if (!*head)
			return (0);
	}
	tem = *head;
	while (tem && (tem)->fd != fd)
	{
		if (!(tem)->next)
		{
			(tem)->next = create_node(fd);
			if (!(tem)->next)
				return (0);
		}
		tem = (tem)->next;
	}
	*cur = tem;
	return (1);
}

int	process_error(t_list **head, t_list *cur, char *str)
{
	t_list	*tem;

	if (str)
		free(str);
	tem = *head;
	if (tem == cur)
	{
		*head = tem->next;
		free(cur);
		return (0);
	}
	while (tem->next)
	{
		if (tem->next == cur)
		{
			tem->next = cur->next;
			free(cur);
			break ;
		}
		tem = tem->next;
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && dstsize && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

char	*append_line(t_list **head, t_list *cur, char **res, int option)
{
	char	*new;

	new = malloc(cur->new_len + cur->len + 1);
	if (!new)
	{
		process_error(head, cur, *res);
		return (FT_NULL);
	}
	if (*res)
	{
		ft_strlcpy(new, *res, cur->new_len + 1);
		free(*res);
	}
	ft_strlcpy(new + cur->new_len, \
				&cur->buff[1 + cur->offset - cur->len], cur->len + 1);
	cur->new_len += cur->len;
	cur->len = 1;
	if (option)
	{
		cur->new_len = 0;
		cur->offset++;
		cur->len = 1;
	}
	*res = new;
	return (new);
}
