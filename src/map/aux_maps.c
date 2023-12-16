/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_maps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:59:15 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/11 17:44:58 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	// Funciones de libft y el write error con mensaje
void	ft_write_error(char *message)
{
    write(2, "Error\n", 6);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    exit(-1);
}
bool	ft_strcmp(char *s1, char *s2)
{
	size_t			cont;

	cont = 0;
	if (s1 == NULL || s2 == NULL)
		return (false);

	while (s1[cont] != '\0')
	{
		if (s1[cont] != s2[cont])
			return (false);
		cont++;
	}
	return (true);
}
void	ft_write(char *message)
{
    write(2, "Error\n", 6);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    return ;
}
bool	ft_check_comas(char *input)
{
	int	c;
	int	coma;

	c = 0;
	coma = 0;
	while (input[c])
	{
		if (input[c] == ',')
			coma++;
		c++;
	}
	if (coma != 2)
		return (false);
	return (true);
}

