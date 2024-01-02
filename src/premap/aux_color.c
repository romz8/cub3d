/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:28:00 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/31 11:32:00 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	n = 0;
	while ((unsigned char)str[i] == ' ' || (unsigned char)str[i] == '\t'
		|| (unsigned char)str[i] == '\n' || (unsigned char)str[i] == '\f'
		|| (unsigned char)str[i] == '\r' || (unsigned char)str[i] == '\v')
		i++;
	if (str[i] == '-')
		sign = -1;
	else
		sign = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		n = 10 * n + (str[i] - '0');
		i++;
	}
	return (sign * n);
}

bool	is_color(int color)
{
	if (color >= 0 && color <= 255)
		return (true);
	return (false);
}

void	ft_check_color(t_map_color *color)
{
	if (!is_color(color->ceil_color->r) || !is_color(color->ceil_color->g)
		|| !is_color(color->ceil_color->b) || !is_color(color->floor_color->r)
		|| !is_color(color->floor_color->g) || !is_color(color->floor_color->b))
		ft_write_error("Error\nBad color number\n");
}
