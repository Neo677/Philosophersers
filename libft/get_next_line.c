/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:07:43 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/24 15:07:45 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	create_lst(t_gnl_list **list, int fd)
{
	int		read_char;
	char	*buf;

	while (!found_nwl(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
		{
			point_mort(list, NULL, NULL);
			return ;
		}
		read_char = read(fd, buf, BUFFER_SIZE);
		if (read_char <= 0)
		{
			free(buf);
			if (read_char < 0)
				point_mort(list, NULL, NULL);
			return ;
		}
		buf[read_char] = '\0';
		list_new(list, buf);
	}
}

char	*get_line(t_gnl_list *list)
{
	int		str_len;
	char	*next_str;

	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	str_cpy(list, next_str);
	return (next_str);
}

void	point_mort(t_gnl_list **list, t_gnl_list *cl_node, char *buf)
{
	t_gnl_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->bufers);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (cl_node && cl_node->bufers[0])
		*list = cl_node;
	else
	{
		free(buf);
		free(cl_node);
	}
}

void	poff_list(t_gnl_list **list)
{
	t_gnl_list	*lt_node;
	t_gnl_list	*cl_node;
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	buf = malloc(BUFFER_SIZE + 1);
	cl_node = malloc(sizeof(t_gnl_list));
	if (!buf || !cl_node)
	{
		return (free(buf), point_mort(list, NULL, NULL));
	}
	lt_node = find_last_node(*list);
	while (lt_node->bufers[i] && lt_node->bufers[i] != '\n')
		i++;
	if (lt_node->bufers[i] == '\n')
		i++;
	while (lt_node->bufers[i])
		buf[j++] = lt_node->bufers[i++];
	buf[j] = '\0';
	cl_node->bufers = buf;
	cl_node->next = NULL;
	point_mort(list, cl_node, buf);
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*list;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_lst(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
	poff_list(&list);
	return (next_line);
}
