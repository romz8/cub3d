/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:26:09 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/31 17:21:48 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*void_free_spaces(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			j++;
		i++;
	}
	result = (char *)malloc(sizeof(char) * j + 2);
	if (!result)
		ft_write_error("Error\nCannot allocate memory for free_spaces\n");
	return (result);
}

char	*process_dir_spaces(char *str, char *result, int *j, int *i)
{
	if (str[*i] && str[*i + 1] && str[*i + 2])
	{
		if ((str[*i] == 'N' && str[*i + 1] == 'O' && str[*i + 2] == ' ')
			|| (str[*i] == 'S' && str[*i + 1] == 'O' && str[*i + 2] == ' ')
			|| (str[*i] == 'W' && str[*i + 1] == 'E' && str[*i + 2] == ' ')
			|| (str[*i] == 'E' && str[*i + 1] == 'A' && str[*i + 2] == ' '))
		{
			result[(*j)++] = str[(*i)++];
			result[(*j)++] = str[(*i)++];
			result[(*j)++] = str[(*i)++];
		}
	}
	return (result);
}

char	*free_spaces(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = void_free_spaces(str);
	while (str[i])
	{
		result = process_dir_spaces(str, result, &j, &i);
		if ((str[i] == 'C' || str[i] == 'F') && (str[i + 1] == ' '))
		{
			result[j++] = str[i++];
			result[j++] = ' ';
		}
		else if (str[i] != ' ')
			result[j++] = str[i++];
		else
			i++;
	}
	result[j] = '\0';
	return (result);
}

int	wordcount(const char *str)
{
	int		count;
	bool	in_word;

	count = 0;
	in_word = false;
	while (*str)
	{
		if (*str == ' ')
			in_word = false;
		else if (!in_word)
		{
			in_word = true;
			count++;
		}
		str++;
	}
	return (count);
}
