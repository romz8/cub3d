/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:24:22 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/14 13:51:24 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_map_color	*init_color(void)
// {
// 	t_map_color	*color;

// 	color = malloc(sizeof(t_map_color));
// 	if (!color)
// 	{
// 		fprintf(stderr, "Error: Unable to allocate memory for t_map_color\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	color->floor_color = malloc(sizeof(t_color));
// 	color->ceil_color = malloc(sizeof(t_color));
// 	if (!color->floor_color || !color->ceil_color)
// 	{
// 		fprintf(stderr, "Error: Unable to allocate memory for t_color within t_map_color\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	color->floor_color->r = 0;
// 	color->floor_color->g = 0;
// 	color->floor_color->b = 0;
// 	color->ceil_color->r = 0;
// 	color->ceil_color->g = 0;
// 	color->ceil_color->b = 0;
// 	return (color);
// }

/*****
 * splitea la cadena con los char numeros por las comas.
 * hace un atoi y lo coloca en la estructura
 **** */

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	get_color_floor(t_map *map, t_textures *texture)
{
	char	*rgb[3];
	char	**char_numbers;
	int		num_elements;

	num_elements = 0;
	char_numbers = ft_split(texture->paths->floor, ',');
	while (char_numbers && char_numbers[num_elements])
		num_elements++;
	if (num_elements == 3)
	{
		rgb[0] = char_numbers[0];
		rgb[1] = char_numbers[1];
		rgb[2] = char_numbers[2];
		if (is_numeric(rgb[0]) && is_numeric(rgb[1]) && is_numeric(rgb[2]))
		{
			map->color_f[0] = ft_atoi(rgb[0]);
			map->color_f[1] = ft_atoi(rgb[1]);
			map->color_f[2] = ft_atoi(rgb[2]);
		}
		else
			ft_write_error("Error\nBad color numbers\n");
	}
	else
		ft_write_error("Error\nBad color numbers\n");
	free_split(char_numbers); // SHOULD IT NOT BE FREED ?
}

void	get_color_ceil(t_map *map, t_textures *texture)
{
	char	*rgb[3];
	char	**char_numbers;
	int		num_elements;

	num_elements = 0;
	char_numbers = ft_split(texture->paths->ceil, ',');
	while (char_numbers && char_numbers[num_elements])
		num_elements++;
	if (num_elements == 3)
	{
		rgb[0] = char_numbers[0];
		rgb[1] = char_numbers[1];
		rgb[2] = char_numbers[2];
		if (is_numeric(rgb[0]) && is_numeric(rgb[1]) && is_numeric(rgb[2]))
		{
			map->color_c[0] = ft_atoi(rgb[0]);
			map->color_c[1] = ft_atoi(rgb[1]);
			map->color_c[2] = ft_atoi(rgb[2]);
		}
		else
			ft_write_error("Error\nBad color numbers\n");
	}
	else
		ft_write_error("Error\nBad color numbers\n");
	free(char_numbers); // SHOULD IT NOT BE FREED ?
}

void	ft_check_color(t_map *map)
{
	if (map->color_c[0]< 0 || map->color_c[1] < 0 ||
		map->color_c[2] < 0 || map->color_c[0] > 255 ||
		map->color_c[1] > 255 || map->color_c[2] > 255 ||
		map->color_f[0] < 0 || map->color_f[1] < 0 ||
		map->color_f[2] < 0 || map->color_f[0] > 255 ||
		map->color_f[1] > 255 || map->color_f[2] > 255)
		ft_write_error("Error\nBad color number\n");
}

/*
convert TRGB to HEX using bitshift as 0xTTRRGGBB = (T, R, G, B)
*/
int	create_hex_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

