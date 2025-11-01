/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahoumi <abahoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 10:15:41 by abahoumi          #+#    #+#             */
/*   Updated: 2025/11/01 14:44:57 by abahoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_file(int fd, char *buffer, char *storage)
{
	ssize_t	read_bytes;
	char	*tmp;

	read_bytes = 1;
	while (read_bytes > 0 && index_of(storage, '\n') == -1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(storage), NULL);
		buffer[read_bytes] = '\0';
		tmp = storage;
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (free(tmp), NULL);
		free(tmp);
	}
	return (storage);
}

char	*extract_line(char *storage)
{
	int	new_line_indx;

	new_line_indx = index_of(storage, '\n');
	if (new_line_indx != -1)
		return (ft_substr(storage, 0, new_line_indx + 1));
	if (*storage)
		return (ft_strdup(storage));
	return (NULL);
}

void	copy_to_buffer(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

void	update_buffer(char *buffer, char *storage)
{
	int		new_line_indx;

	new_line_indx = index_of(storage, '\n');
	if (new_line_indx != -1)
		copy_to_buffer(buffer, storage + new_line_indx + 1, BUFFER_SIZE);
	free(storage);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE][OPEN_MAX];
	char		*line;
	char		*storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = ft_strdup(buffer[fd]);
	if (!storage)
		return (NULL);
	if (index_of(storage, '\n') == -1)
		storage = read_file(fd, buffer[fd], storage);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	update_buffer(buffer[fd], storage);
	return (line);
}
