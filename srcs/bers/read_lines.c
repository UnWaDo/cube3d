/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:47:13 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:47:13 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>

static int	proceed_line(t_list **lst, char *line)
{
	t_list	*new;

	new = ft_lstnew(line);
	if (!new)
		return (1);
	ft_lstadd_back(lst, new);
	return (0);
}

static t_list	*read_map_lines(int fd)
{
	char	*line;
	t_list	*lst;

	line = get_next_line(fd);
	lst = NULL;
	while (line)
	{
		if (proceed_line(&lst, line))
			break ;
		line = get_next_line(fd);
	}
	if (line)
	{
		free(line);
		ft_lstclear(&lst, &free);
	}
	return (lst);
}

static void	remove_endlines(t_list *lst)
{
	size_t	len;
	char	*line;

	while (lst)
	{
		line = lst->content;
		lst = lst->next;
		len = ft_strlen(line);
		if (!len)
			continue ;
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
}

t_list	*read_lines(char *file)
{
	t_list	*lst;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error_with_add(MAP_FILE_ERR, file);
		perror(NULL);
		return (NULL);
	}
	if (read(fd, NULL, 0) < 0)
	{
		print_error_with_add(MAP_READ_ERR, file);
		perror(NULL);
		close(fd);
		return (NULL);
	}
	lst = read_map_lines(fd);
	close(fd);
	if (!lst)
		print_error(MAP_ALLOC_ERR);
	if (lst)
		remove_endlines(lst);
	return (lst);
}
