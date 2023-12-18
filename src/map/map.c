/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:42:22 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/14 19:24:54 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		ft_write("Error\nCan't allocate memorry for map\n");
		return (NULL);
	}
	map->map_raw = NULL;
	map->map_2d = NULL;
	map->max_height = 0;
	map->max_width = 0;
	printf("Map initialized successfully.\n");
	return (map);
}

void	create_2d(t_map *map)
{
	char	**map_2d;
	int		i;
	int		j;

	i = 0;
	map_2d = (char **)malloc((map->max_height) * sizeof(char *));
	if (!map_2d)
	{
		ft_write("Error\nCan't allocate memorry for map 2d\n");
		return ;
	}
	while (i < map->max_height)
	{
		j = 0;
		map_2d[i] = (char *)malloc((map->max_width) * sizeof(char));
		while (j < map->max_width)
		{
			map_2d[i][j] = ' ';
			j++;
		}
		i++;
	}
	map->map_2d = map_2d;
}

void	handle_slash_en(t_map *map, int *y, int *k, int *x)
{
	(*x) = 1;
	(*y)++;
	(*k)++;
	(void) map; // same unused map var
}

void	handle_tabs(t_map *map, int y, int *x, int *k)
{
	int	i;

	i = 0;
	while (i < 4 && *x < map->max_width - 1)
	{
		map->map_2d[y][(*x)] = ' ';
		(*x)++;
		i++;
	}
	(*k)++;
}

void	copy_line_to_map(t_map *map)
{
	int	y;
	int	x;
	int	k;

	y = 2;
	x = 1;
	k = 0;
	while (y <= map->max_height - 1 && map->map_raw[k] != '\0')
	{
		while (x <= map->max_width - 1)
		{
			if (map->map_raw[k] != '\n' && map->map_raw[k] != '\0'
				&& map->map_raw[k] != '\t')
				map->map_2d[y][x++] = map->map_raw[k++];
			else if (map->map_raw[k] == '\t')
				handle_tabs(map, y, &x, &k);
			else if (map->map_raw[k] == '\n')
				handle_slash_en(map, &y, &k, &x);
			else
				break ;
		}
	}
}
