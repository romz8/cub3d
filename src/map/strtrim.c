/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurcia- <amurcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:55:13 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/24 16:20:28 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	find_start(char const *s1, char const *set, int len)
{
	int	l_s1;

	l_s1 = 0;
	while (l_s1 < len)
	{
		if (ft_strchr(set, s1[l_s1]))
			l_s1++;
		else
			break ;
	}
	return (l_s1);
}

int	find_end(char const *s1, char const *set, int len)
{
	int	l_s2;

	l_s2 = 0;
	while (l_s2 < len)
	{
		if (ft_strchr(set, s1[len - l_s2 - 1]))
			l_s2++;
		else
			break ;
	}
	return (l_s2);
}

void	complete_str(char *str, char const *s1, int l_s1, int l_s2)
{
	int	c;
	int	len;

	len = ft_strlen((char *)s1);
	c = 0;
	while (c < (len - l_s2 - l_s1) && s1[c + l_s1])
	{
		str[c] = s1[c + l_s1];
		c++;
	}
	str[c] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		l_s1;
	int		l_s2;
	int		c;
	char	*str;

	if (!s1)
		return (NULL);
	len = ft_strlen((char *)s1);
	l_s1 = find_start(s1, set, len);
	l_s2 = find_end(s1, set, len);
	c = len - l_s1 - l_s2;
	if (c < 0)
		c = 0;
	str = malloc(sizeof(char) * (c + 1));
	if (str == NULL)
		return (NULL);
	if (c == 0)
	{
		str[0] = '\0';
		return (str);
	}
	complete_str(str, s1, l_s1, l_s2);
	return (str);
}
