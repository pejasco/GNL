/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:42:31 by chuleung          #+#    #+#             */
/*   Updated: 2023/11/28 17:57:52 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content_buf;
	struct s_list	*next;
}	t_list;

int		find_new_line(t_list *list);
t_list	*find_last_node(t_list *list);
int		get_str_len(t_list *list);
void	free_nodes(t_list **list, t_list *new_header_node, char *buffer);
void	ft_strcpy(char *str, t_list *list);
void	rearrange_list(t_list **list);
char	*full_line(t_list *list);
void	append_list(t_list **list, char *buffer);
char	*get_next_line(int fd);

#endif
