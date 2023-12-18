/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:59:29 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/13 19:35:19 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_textures	*init_textures(void)
{
	t_textures	*texture;
	texture = malloc(sizeof(t_textures));
	if (!texture)
	{
		ft_write("Error\n Allocating memory for map\n");
		return (NULL);
	}
	// Inicializar la estructura con valores predeterminados o nulos
	texture->type = UNKNOWN;
	texture->path = NULL;
	texture->texture_raw = NULL;
	texture->info = NULL;

// Inicializar la estructura t_cardinal dentro de t_textures
	texture->paths = (t_cardinal *)malloc(sizeof(t_cardinal));
	if (texture->paths == NULL)
	{
// Manejo de error: No se pudo asignar memoria
	exit(EXIT_FAILURE);
	}

// Inicializar los campos de t_cardinal
	texture->paths->north = NULL;
	texture->paths->south = NULL;
	texture->paths->east = NULL;
	texture->paths->west = NULL;
	texture->paths->floor = NULL;
	texture->paths->ceil = NULL;
	return(texture);
}
