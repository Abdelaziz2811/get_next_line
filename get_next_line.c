/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahoumi <abahoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 10:15:41 by abahoumi          #+#    #+#             */
/*   Updated: 2025/10/31 16:28:02 by abahoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *storage)
{
	char	*buffer;
	ssize_t	read_bytes;
	char	*tmp;

	buffer = malloc(sizeof(char) * (size_t)(BUFFER_SIZE + 1));
	if (!buffer)
		return (free(storage), NULL);
	if (!storage)
		storage = ft_strdup("");
	if (!storage)
		return (free(buffer), NULL);
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
	{
		free(storage);
		return (NULL);
	}
	new_storage = ft_strdup(storage + new_line_indx + 1);
	free(storage);
	if (!new_storage || !*new_storage)
	{
		free(new_storage);
		return (NULL);
	}
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (index_of(storage, '\n') == -1)
		storage = read_file(fd, storage);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	storage = update_storage(storage);
	return (line);
}
