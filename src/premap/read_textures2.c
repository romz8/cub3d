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
	if ((str[*i] == 'N' && str[*i + 1] == 'O')
		|| (str[*i] == 'S' && str[*i + 1] == 'O')
		|| (str[*i] == 'W' && str[*i + 1] == 'E')
		|| (str[*i] == 'E' && str[*i + 1] == 'A'))
	{
		result[(*j)++] = str[(*i)++];
		result[(*j)++] = str[(*i)++];
		result[(*j)++] = ' ';
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
