/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:56:40 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/30 12:29:24 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_colors(char **col)
{
	int	i;

	i = 0;
	while (col[i])
	{
		free(col[i]);
		col[i] = NULL;
		i++;
	}
	free(col);
	col = NULL;
}
