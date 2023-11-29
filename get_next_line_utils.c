/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:55:54 by chuleung          #+#    #+#             */
/*   Updated: 2023/11/22 19:21:13 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
#include "get_next_line.h"
//#include <stdlib.h>
//#include <stdio.h>

/*
Checking if there is '\n' character
*/
int	find_new_line(t_list *list)
{
	int		i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content_buf[i] && i < BUFFER_SIZE)
		{
			if (list->content_buf[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

/*
finding the last node which helps appending the list
*/
t_list	*find_last_node(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/*
for copying the buffers stored in the list to the string 
*/
void	ft_strcpy(char *str, t_list *list)
{
	int	i;
	int	k;

	if (list == NULL)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->content_buf[i])
		{
			if (list->content_buf[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->content_buf[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

/*
finding the length of the whole next line 
*/
int	get_str_len(t_list *list)
{
	int		i;
	int		len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content_buf[i])
		{
			if (list->content_buf[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

/* 
##freeing the list##
	a)header node pointing to the remaining part of the 
	last buffer which belongs to the next next line
	b)freeing and clearing the content and addresses 
	of every nodes relevant to the next line
*/
void	free_nodes(t_list **list, t_list *new_header_node, char *buffer)
{
	t_list	*temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content_buf);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (new_header_node->content_buf[0])
		*list = new_header_node;
	else
	{
		free(buffer);
		free(new_header_node);
	}
}
