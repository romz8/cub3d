/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:59:44 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/14 19:30:43 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void    get_player(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->max_height)
	{
//		printf("%c", map->map_2d[y][x]);
		x = 0;
//		printf("\n");
		while (x < map->max_width)
		{
//			printf("%c", map->map_2d[y][x]);
			if (map->map_2d[y][x] == 'N' || map->map_2d[y][x] == 'S'
				|| map->map_2d[y][x] == 'W' || map->map_2d[y][x] == 'E')
			{
				map->p_pos[0] = x;
				map->p_pos[1] = y;
				get_player_direction(map, y, x);
				return ;
			}
			x++;
		}
		y++;
	}
	ft_write_error("Error\nPlayer position not found\n");
}

void	get_player_direction(t_map *map, int y, int x)
{
	if (map->map_2d[y][x] == 'N')
		map->p_direction = 'N';
	else if (map->map_2d[y][x] == 'S')
		map->p_direction = 'S';
	else if (map->map_2d[y][x] == 'W')
		map->p_direction = 'W';
	else if (map->map_2d[y][x] == 'E')
		map->p_direction = 'E';
	//printf("player position--  x = %lf-- y = %lf--\nPlayer direction = x = %lf-- y = %lf--", player->px, player->py, player->dirx, player->diry);
	map->map_2d[y][x] = '0';
//	print_filled_map(map);
	// if (!check_map(map))
	// 	ft_write_error("Error\nThe map is not closed or are spaces inside\n");
	printf("player position is x,y = %i, %i\n", x, y);
}

bool	is_space_around(t_map *map, int y, int x)
{
	if (map->map_2d[y - 1][x] == ' ')
		return (true);
	else if  (map->map_2d[y + 1][x] == ' ')
		return (true);
	else if (map->map_2d[y][x - 1] == ' ')
		return (true);
	else if (map->map_2d[y][x + 1] == ' ')
		return (true);
	else
		return (false);
}

bool	check_map(t_map *map)
{
	int y;
	int	x;

	y = 1;
	while (y < map->max_height)
	{
		x = 1;
        while (x < map->max_width)
		{
			if (map->map_2d[y][x] == '0' && is_space_around(map, y, x))
				return (false);  // Si hay un '0' rodeado por ' ', retorna falso
			x++;
		}
		y++;
	}
	return (true);  // Si no se encontraron problemas, retorna verdadero
}
