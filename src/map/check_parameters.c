/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurcia- <amurcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:25:22 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/29 14:05:49 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_check_nbr_arguments(int argc)
{
	if (argc != 2)
	{
		ft_write_error("You should have 2 arguments\n");
		return (false);
	}
	return (true);
}

bool	ft_check_extension(char **argv)
{
	char	*name;
	char	*term;
	int		len;
	int		i;

	name = ft_strdup(argv[1]);
	term = ".cub";
	len = ft_strlen(name);
	i = 0;
	if (len < 5)
		return (false);
	len -= 4;
	while (name[len] != '\0' && name[len] == term[i])
	{
		len++;
		i++;
	}
	free(name);
	return (term[i] == '\0');
}

void	ft_check_parameters(int argc, char **argv)
{
	if (!ft_check_nbr_arguments(argc))
		ft_write_error("Error.\nUsage: ./your_program map.cub");
	if (!ft_check_extension(argv))
		ft_write_error("Error.\nThe file should be a .cub");
}
