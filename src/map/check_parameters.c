/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:25:22 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/14 18:03:25 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	transfer_texture(t_textures *texture, t_map *map);

bool	ft_check_nbr_arguments(int argc)
{
	if (argc != 2)
	{
		ft_write_error("You should have 2 arguments\n");
		return(false);
	}
	return(true);
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

void 	ft_check_parameters(int argc, char **argv)
{
	if (!ft_check_nbr_arguments(argc))
		ft_write_error("Error.\nUsage: ./your_program map.cub");
	if (!ft_check_extension(argv))
		ft_write_error("Error.\nThe file should be a .cub");
}

t_map *ft_start_map(char **argv)
{
	t_map	*map;
	t_textures *texture;
	
	map	= init_map();
	texture = init_textures();
	ft_read_map(argv, map);
	create_2d(map);
	copy_line_to_map(map);
	get_player(map);
	ft_read_textures(argv, texture);
    process_texture_raw(texture);
	get_color_floor(map, texture);
	get_color_ceil(map, texture);
	ft_check_color(map);
	transfer_texture(texture, map);
	printf("texture NO path is %s\n", texture->paths->north);
	printf("texture SO path is %s\n", texture->paths->south);
	printf("texture W path is %s\n", texture->paths->west);
	printf("texture E path is %s\n", texture->paths->east);
	printf("texture NO path is %s\n", map->texture[0]);
	printf("texture SO path is %s\n", map->texture[1]);
	printf("texture W path is %s\n", map->texture[2]);
	printf("texture E path is %s\n", map->texture[3]);
	return(map);
}

void	transfer_texture(t_textures *texture, t_map *map)
{
	if (texture->paths->north)
	{
		map->texture[0] = texture->paths->north;
		//free(texture->paths->north);
	}
	if (texture->paths->south)
	{
		map->texture[1] = texture->paths->south;
		//free(texture->paths->south);
	}
	if (texture->paths->west)
	{
		map->texture[2] = texture->paths->west;
		//free(texture->paths->west);
	}
	if (texture->paths->east)
	{
		map->texture[3] = texture->paths->east;
		//free(texture->paths->south);
	}
}


