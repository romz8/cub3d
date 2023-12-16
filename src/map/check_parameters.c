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
	t_map_color *color;
	t_textures *texture;
	
	map	= init_map();
	texture = init_textures();
	color = init_color();
	ft_read_map(argv, map);
	create_2d(map);
//	print_filled_map(map);
	copy_line_to_map(map);
	get_player(map);
	printf("IN START_MAP : NO SF HERE \n");
//	print_filled_map(map);
	ft_read_textures(argv, texture);
    // Procesar y mostrar información de texturas
    process_texture_raw(texture);
//    printf("\nPaths:\n");
//    printf("North: %s\n", texture->paths->north);
//    printf("South: %s\n", texture->paths->south);
//    printf("West: %s\n", texture->paths->west);
//    printf("East: %s\n", texture->paths->east);
//    printf("Floor: %s\n", texture->paths->floor);
//    printf("Ceil: %s\n", texture->paths->ceil);
	get_color_floor(color, texture);
	get_color_ceil(color, texture);
	ft_check_color(color);
	map->color_c = color->ceil_color;
	map->color_f = color->floor_color;
	return(map);
}
