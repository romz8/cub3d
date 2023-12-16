/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:10:05 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/13 15:01:07 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_substr_m(char const *s, unsigned int start, size_t len)
{
	char	*str_nueva;
	size_t	len_s;
	size_t	cont;

	len_s = 0;
	while (s[len_s])
		len_s++;
	if (len_s < start)
		len = 0;
	else if (len >= (len_s - start))
		len = len_s - start;
	str_nueva = malloc(sizeof(char) * (len + 1));
	if (!str_nueva)
		return (NULL);
	cont = 0;
	while (cont < len)
	{
		str_nueva[cont] = s[start];
		cont++;
		start++;
	}
	str_nueva[cont] = '\0';
	return (str_nueva);
}

char	*ft_strchr(const char *s, int c)
{
	int	cont;

	cont = 0;
	while (s[cont] != '\0')
	{
		if (s[cont] == (char)c)
			return ((char *)(s + cont));
		cont++;
	}
	if (s[cont] == (char)c)
		return ((char *)(s + cont));
	return (NULL);
}

char	*ft_cutword(char *prt)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (prt[i] != '\n' && prt[i])
		i++;
	if (!prt[i])
	{
		free(prt);
		return (NULL);
	}
	if (prt[i] == '\n')
		i++;
	dest = malloc(sizeof(char) * (ft_strlen(prt) - i + 1));
	if (!dest)
		return (NULL);
	while (prt[i])
		dest[j++] = prt[i++];
	dest[j] = '\0';
	free(prt);
	return (dest);
}

char	*ft_read(int fd, char *ptr)
{
	int		bytes;
	char	*temp;

	bytes = 1;
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (!ft_strchr(ptr, '\n') && bytes != 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(temp);
			free(ptr);
			return (NULL);
		}
		temp[bytes] = '\0';
		ptr = ft_strjoin(ptr, temp);
	}
	free(temp);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*ptr;
	char		*line;
	int			cont;

	cont = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ptr)
		ptr = ft_strdup("");
//	if (!handle_blank_lines(fd, &ptr))
//		return (NULL);
	ptr = ft_read(fd, ptr);
	if (!ptr)
	{
		free(ptr);
		return (NULL);
	}
	while (ptr[cont] != '\n' && ptr[cont])
		cont++;
	line = ft_substr_m(ptr, 0, cont + 1);
	ptr = ft_cutword(ptr);
	if (!line || !line[0])
	{
		free(line);
		return (NULL);
	}
	return (line);
}
