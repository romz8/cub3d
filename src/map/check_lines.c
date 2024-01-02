/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:55:13 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/31 18:02:04 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W')
		return (true);
	return (false);
}

bool	skip_whitespace(char *line, int *length)
{
	*length = 0;
	while (line[*length] == ' ')
	{
		(*length)++;
		if (line[*length] == '\0')
			return (false);
	}
	return (true);
}

bool	is_valid_map_line(char *line)
{
	int		length;
	bool	map_started;

	length = 0;
	map_started = false;
	while (line[length] == ' ')
		if (!skip_whitespace(line, &length))
			return (false);
	while (line[length])
	{
		if (is_map_char(line[length]))
		{
			map_started = true;
			length++;
		}
		else if ((line[length] == '\n' || line[length] == ' ')
			&& map_started)
			length++;
		else
			return (false);
	}
	return (true);
}

bool	is_valid_line_inside(char *line)
{
	int	length;

	length = 0;
	while (line[length])
	{
		if ((is_map_char(line[length]) || line[length] == '\n'
				|| line[length] == ' '))
			length++;
		else
			return (false);
	}
	return (true);
}

bool	not_allowed_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			return (true);
		i++;
	}
	return (false);
}
