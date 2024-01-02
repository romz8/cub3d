/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:24:22 by frmurcia          #+#    #+#             */
/*   Updated: 2024/01/02 10:14:25 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_color	init_color(t_map_color *color)
{
	color->floor_color = malloc(sizeof(t_color));
	color->ceil_color = malloc(sizeof(t_color));
	if (!color->floor_color || !color->ceil_color)
		ft_write_error("Error\nUnable to allocate memory for t_color\n");
	color->floor_color->r = 0;
	color->floor_color->g = 0;
	color->floor_color->b = 0;
	color->ceil_color->r = 0;
	color->ceil_color->g = 0;
	color->ceil_color->b = 0;
	return (*color);
}

/*****
 * splitea la cadena con los char numeros por las comas.
 * hace un atoi y lo coloca en la estructura
 **** */
void	get_color_floor(t_map_color *color, t_textures *texture)
{
	char	**char_numbers;
	int		num_elements;

	num_elements = 0;
	char_numbers = ft_split(texture->paths->floor, ',');
	while (char_numbers && char_numbers[num_elements]
		&& is_numeric(char_numbers[num_elements]))
		num_elements++;
	if (num_elements == 3)
	{
		color->floor_color->r = ft_atoi(char_numbers[0]);
		color->floor_color->g = ft_atoi(char_numbers[1]);
		color->floor_color->b = ft_atoi(char_numbers[2]);
		free_colors(char_numbers);
	}
	else
		ft_write_error("Error\nBad color numbers\n");
	color->floor_color->hex = create_hex_color(color->floor_color->r,
			color->floor_color->g, color->floor_color->b);
}

void	get_color_ceil(t_map_color *color, t_textures *texture)
{
	char	**char_numbers;
	int		num_elements;

	num_elements = 0;
	char_numbers = ft_split(texture->paths->ceil, ',');
	while (char_numbers && char_numbers[num_elements]
		&& is_numeric(char_numbers[num_elements]))
		num_elements++;
	if (num_elements == 3)
	{
		color->ceil_color->r = ft_atoi(char_numbers[0]);
		color->ceil_color->g = ft_atoi(char_numbers[1]);
		color->ceil_color->b = ft_atoi(char_numbers[2]);
		free_colors(char_numbers);
	}
	else
		ft_write_error("Error\nBad color arguments\n");
	color->ceil_color->hex = create_hex_color(color->ceil_color->r,
			color->ceil_color->g, color->ceil_color->b);
}

unsigned int	create_hex_color(int r, int g, int b)
{
	return (((r & 0xff) << 16)
		+ ((g & 0xff) << 8)
		+ (b & 0xff));
}

int	create_hex_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
