/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurcia- <amurcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:42:22 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/29 15:32:02 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	init_map(t_map *map)
{
	map->map_raw = NULL;
	map->max_height = 0;
	map->max_width = 0;
	map->map_2d = NULL;
	return (*map);
}

void	create_2d(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->map_2d = (char **)malloc((map->max_height) * sizeof(char *));
	if (!map->map_2d)
		ft_write_error("Error\nCan't allocate memorry for map 2d\n");
	map->map_2d[map->max_height] = NULL;
	while (i < map->max_height)
	{
		j = 0;
		map->map_2d[i] = (char *)malloc((map->max_width) * sizeof(char));
		if (!map->map_2d[i])
			ft_write_error("Error\nCan't allocate memorry for map 2d\n");
		map->map_2d[i][map->max_width] = '\0';
		while (j < map->max_width)
		{
			map->map_2d[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void	handle_slash_en(int *y, int *k, int *x)
{
	(*x) = 1;
	(*y)++;
	(*k)++;
}

void	copy_line_to_map(t_map *map)
{
	int	y;
	int	x;
	int	k;

	y = 1;
	x = 1;
	k = 0;
	while (y <= map->max_height - 1 && map->map_raw[k] != '\0')
	{
		x = 1;
		while (x <= map->max_width - 1)
		{
			if (map->map_raw[k] != '\n' && map->map_raw[k] != '\0')
				map->map_2d[y][x++] = map->map_raw[k++];
			else if (map->map_raw[k] == ' ')
			{
				map->map_2d[y][x++] = ' ';
				k++;
			}
			else if (map->map_raw[k] == '\n')
				handle_slash_en(&y, &k, &x);
			else
				break ;
		}
	}
}
