/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:05:33 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/24 16:13:57 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	*free_malloc(char *str)
{
	free(str);
	return (NULL);
}

int	contain_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	get_storage_len(char *storage)
{
	if (storage)
		return (ft_strlen(storage));
	else
		return (0);
}

char	*concat_str(char *storage, char *buffer, int len_b)
{
	int		i;
	int		len_s;
	char	*str;

	len_s = get_storage_len(storage);
	str = malloc(sizeof(char) * (len_s + len_b + 1));
	if (str == NULL)
		return (free_malloc(storage));
	i = 0;
	while (i < len_s)
	{
		str[i] = storage[i];
		i++;
	}
	i = 0;
	while (i < len_b)
	{
		str[len_s + i] = buffer[i];
		i++;
	}
	str[len_s + i] = '\0';
	free(storage);
	return (str);
}
