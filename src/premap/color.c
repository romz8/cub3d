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

t_map_color	*init_color(void)
{
	t_map_color	*color;

	color = malloc(sizeof(t_map_color));
	if (!color)
	{
		fprintf(stderr, "Error: Unable to allocate memory for t_map_color\n");
		exit(EXIT_FAILURE);
	}
	color->floor_color = malloc(sizeof(t_color));
	color->ceil_color = malloc(sizeof(t_color));
	if (!color->floor_color || !color->ceil_color)
	{
		fprintf(stderr, "Error: Unable to allocate memory for t_color within t_map_color\n");
		exit(EXIT_FAILURE);
	}
	color->floor_color->r = 0;
	color->floor_color->g = 0;
	color->floor_color->b = 0;
	color->ceil_color->r = 0;
	color->ceil_color->g = 0;
	color->ceil_color->b = 0;
	return (color);
}

/*****
 * splitea la cadena con los char numeros por las comas.
 * hace un atoi y lo coloca en la estructura
 **** */
void	get_color_floor(t_map_color *color, t_textures *texture)
{
	char	*r;
	char	*g;
	char	*b;
	char	**char_numbers;
	int		num_elements;

	num_elements = 0;
	char_numbers = ft_split(texture->paths->floor, ',');
	while (char_numbers && char_numbers[num_elements])
		num_elements++;
	if (num_elements == 3)
	{
		r = char_numbers[0];
		g = char_numbers[1];
		b = char_numbers[2];
		if (is_numeric(r) && is_numeric(g) && is_numeric(b))
		{
			color->floor_color->r = ft_atoi(r);
			color->floor_color->g = ft_atoi(g);
			color->floor_color->b = ft_atoi(b);
		}
		else
			ft_write_error("Error\nBad color numbers\n");
		color->floor_color->hex = create_hex_color(ft_atoi(r), ft_atoi(g), ft_atoi(b));
		printf("Hex color floor: 0x%X\n", color->floor_color->hex);
	}
	else
		ft_write_error("Error\nBad color numbers\n");
}

void	get_color_ceil(t_map_color *color, t_textures *texture)
{
	char	*r;
	char	*g;
	char	*b;
	char	**char_numbers;
	int		num_elements;

	num_elements = 0;
	char_numbers = ft_split(texture->paths->ceil, ',');
	while (char_numbers && char_numbers[num_elements])
		num_elements++;
	if (num_elements == 3)
	{
		r = char_numbers[0];
		g = char_numbers[1];
		b = char_numbers[2];
		if (is_numeric(r) && is_numeric(g) && is_numeric(b))
		{
			color->ceil_color->r = ft_atoi(r);
			color->ceil_color->g = ft_atoi(g);
			color->ceil_color->b = ft_atoi(b);
		}
		else
			ft_write_error("Error\nBad color arguments\n");
		color->ceil_color->hex = create_hex_color(ft_atoi(r), ft_atoi(g), ft_atoi(b));
		printf("Hex color ceil: 0x%X\n", color->ceil_color->hex);
	}
}

void	ft_check_color(t_map_color *color)
{
	if (color->ceil_color->r < 0 || color->ceil_color->g < 0 ||
		color->ceil_color->b < 0 || color->ceil_color->r > 255 ||
		color->ceil_color->g > 255 || color->ceil_color->b > 255 ||
		color->floor_color->r < 0 || color->floor_color->g < 0 ||
		color->floor_color->b < 0 || color->floor_color->r > 255 ||
		color->floor_color->g > 255 || color->floor_color->b > 255)
		ft_write_error("Error\nBad color number\n");
}

unsigned int	create_hex_color(int r, int g, int b)
{
	printf("R: %i  G: %i  B: %i\n", r, g, b);
	return (
		((r & 0xff) << 16) +
		((g & 0xff) << 8) +
		(b & 0xff) 
	);
}

