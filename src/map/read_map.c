/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:27:50 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/09 19:48:09 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_empty_or_spaces(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n'
			&& *line != '\r' && *line != '\f' && *line != '\v')
			return (false);
		line++;
	}
	return (true);
}

void	process_map_line(t_map *map, char *line, int *line_number)
{
	static int	found_content = 0;
	static int  found_void = 0;

	if (!map->map_raw && is_valid_map_line(line, map))
	{
		map->map_raw = ft_strdup(line);
		map->map_start = *line_number;
		found_content = 1;
	}
	else if (map->map_raw && is_valid_line_inside(line, map) && !(is_empty_or_spaces(line)))
	{
		map->map_raw = ft_strjoin(map->map_raw, line);
		found_void = 0;
	}
	else if (map->map_raw && is_valid_line_inside(line, map) && is_empty_or_spaces(line))
    {
		found_void = 1;
		if (found_content && found_void)
			ft_write_error("Error. Bad map!\n");
	}
	(*line_number)++;
	free(line);
}

int	set_measures_and_close(t_map *map, int line_number, int fd)
{
	map->map_end = line_number;
	map->max_height = map->map_end - map->map_start + 3;
	printf("Max height = %i\n", map->max_height);
	if (close(fd) == -1)
		ft_write_error("Error closing file descriptor\n");
	return (fd);
}

void	ft_read_map(char **argv, t_map *map)
{
	int		fd;
	char	*line;
	int		line_number;

	line_number = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_write_error("Error opening map file\n");
	line = get_next_line(fd);
	if (!line)
		ft_write_error("Error reading lines of the map\n");
	map->map_raw = NULL;
	while (line)
	{
		process_map_line(map, line, &line_number);
		line = get_next_line(fd);
		if (!line)
		{
			map->map_end = line_number;
			break ;
		}
	}
	free(line);
	set_measures_and_close(map, line_number, fd);
}

void	print_filled_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->max_height)
	{
		j = 0;
		while (j < map->max_width)
		{
			printf("%c", map->map_2d[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("\n");
}
