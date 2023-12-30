/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurcia- <amurcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:59:29 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/30 12:00:16 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	are_texture_paths_filled(t_cardinal *paths)
{
	return (paths->north && paths->south && paths->east && paths->west
		&& paths->floor && paths->ceil);
}

t_textures	init_textures(t_textures *texture)
{
	texture->type = UNKNOWN;
	texture->path = NULL;
	texture->texture_raw = NULL;
	texture->info = NULL;
	texture->paths = (t_cardinal *)malloc(sizeof(t_cardinal));
	if (!texture->paths)
		ft_write_error("Error\n Can't initilize paths\n");
	texture->paths->north = NULL;
	texture->paths->south = NULL;
	texture->paths->east = NULL;
	texture->paths->west = NULL;
	texture->paths->floor = NULL;
	texture->paths->ceil = NULL;
	return (*texture);
}

void	free_textures(t_textures *texture)
{
	int	i;

	i = 0;
	if (texture)
	{
		if (texture->path != NULL)
			free(texture->path);
		if (texture->texture_raw)
			free(texture->texture_raw);
		if (texture->paths->north)
			free(texture->paths->north);
		if (texture->paths->south)
			free(texture->paths->south);
		if (texture->paths->east)
			free(texture->paths->east);
		if (texture->paths->west)
			free(texture->paths->west);
		if (texture->paths->floor)
			free(texture->paths->floor);
		if (texture->paths->ceil)
			free(texture->paths->ceil);
	}
}
