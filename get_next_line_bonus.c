/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahoumi <abahoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 10:15:41 by abahoumi          #+#    #+#             */
/*   Updated: 2025/11/04 13:20:23 by abahoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_file(int fd, char *storage)
{
	char	*buffer;
	ssize_t	read_bytes;
	char	*tmp;

	buffer = malloc(sizeof(char) * (size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(storage), NULL);
	read_bytes = 1;
	while (read_bytes > 0 && index_of(storage, '\n') == -1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(buffer), free(storage), NULL);
		buffer[read_bytes] = '\0';
		tmp = storage;
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (free(buffer), free(tmp), NULL);
		free(tmp);
	}
	return (free(buffer), storage);
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

char	*update_storage(char *storage)
{
	int		new_line_indx;
	char	*new_storage;

	new_line_indx = index_of(storage, '\n');
	if (new_line_indx == -1)
		return (free(storage), NULL);
	new_storage = ft_strdup(storage + new_line_indx + 1);
	free(storage);
	if (!new_storage)
		return (NULL);
	if (!*new_storage)
		return (free(new_storage), NULL);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	if (index_of(storage[fd], '\n') == -1)
		storage[fd] = read_file(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = extract_line(storage[fd]);
	storage[fd] = update_storage(storage[fd]);
	return (line);
}
