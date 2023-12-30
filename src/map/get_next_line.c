/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurcia- <amurcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:10:05 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/24 16:11:37 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_line_words(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
		i++;
	return (i + 1);
}

void	clean_storage(char *storage)
{
	int	old_len;
	int	new_len;
	int	i;

	old_len = count_line_words(storage);
	new_len = ft_strlen(storage) - old_len;
	i = 0;
	while (i < new_len)
	{
		storage[i] = storage[old_len + i];
		i++;
	}
	while (i < old_len)
	{
		storage[i] = '\0';
		i++;
	}
	storage[i] = '\0';
}

char	*extract_line(char *str)
{
	int		words;
	int		i;
	char	*line;

	words = count_line_words(str);
	line = malloc(sizeof(char) * (words + 1));
	if (line == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (i < words)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	clean_storage(str);
	return (line);
}

char	*extract_last_line(char *str, int numbytes, char *buffer)
{
	int		words;
	int		i;
	char	*line;

	free(buffer);
	if (str == NULL || numbytes == -1)
		return (free_malloc(str));
	if (str[0] == '\0')
		return (free_malloc(str));
	words = ft_strlen(str);
	line = malloc(sizeof(char) * (words + 1));
	if (line == NULL)
		return (free_malloc(str));
	i = 0;
	while (i < words)
	{
		line[i] = str[i];
		str[i] = '\0';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*storage;
	int			numbytes;

	if (fd < 0 || fd <= 0)
		return (NULL);
	if (storage && contain_line(storage) == 1)
		return (extract_line(storage));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (free_malloc(storage));
	numbytes = read(fd, buffer, BUFFER_SIZE);
	if (numbytes == 0 || numbytes == -1)
		return (extract_last_line(storage, numbytes, buffer));
	buffer[BUFFER_SIZE] = '\0';
	storage = concat_str(storage, buffer, numbytes);
	free(buffer);
	buffer = NULL;
	if (storage == NULL)
		return (NULL);
	return (get_next_line(fd));
}
