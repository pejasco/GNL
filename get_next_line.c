/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:32:25 by chuleung          #+#    #+#             */
/*   Updated: 2023/11/22 19:27:27 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
//#include <stdlib.h>
//#include <stdio.h>
#include "get_next_line.h"

/* 
##rearranging the list##
	a)redriecting header node to next next line
	b)freeing the memory of the nodes relevant to the next line
*/
void	rearrange_list(t_list **list)
{
	t_list	*last_node;
	t_list	*new_header_node;
	int		i;
	int		x;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	new_header_node = malloc(sizeof(t_list));
	if (buffer == NULL || new_header_node == NULL)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	x = 0;
	while (last_node->content_buf[i] && last_node->content_buf[i] != '\n')
		++i;
	while (last_node->content_buf[i] && last_node->content_buf[++i])
		buffer[x++] = last_node->content_buf[i];
	buffer[x] = '\0';
	new_header_node->content_buf = buffer;
	new_header_node->next = NULL;
	free_nodes(list, new_header_node, buffer);
}

/* 
##function-reporting the next line##
	-concatenating the buffers relevant to the next line
*/
char	*full_line(t_list *list)
{
	int		str_len;
	char	*full_line;

	if (list == NULL)
		return (NULL);
	str_len = get_str_len(list);
	full_line = malloc(str_len + 1);
	if (full_line == NULL)
		return (NULL);
	ft_strcpy(full_line, list);
	return (full_line);
}

/* 
##appending the list##
	-appending the list if there is a new buffer
*/
void	append_list(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content_buf = buffer;
	new_node->next = NULL;
}

/* 
Creating the linked list:
	-head node pointing to the remaining part 
	of the last buffer which belongs to the next line
	-freeing the memory of the nodes relevant 
	to the previous line
*/
void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buffer;

	while (!find_new_line(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (!char_read)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		append_list(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	if (list == NULL)
		list = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = full_line(list);
	rearrange_list(&list);
	return (next_line);
}

/*#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int fd = open("file.txt", O_RDONLY);
    char *line;

    if (fd == -1) {
        printf("Failed to open file\n");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s\n", line);
        free(line);
    }

    close(fd);

    return 0;
}*/
