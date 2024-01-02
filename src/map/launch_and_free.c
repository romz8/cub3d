/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:40:51 by frmurcia          #+#    #+#             */
/*   Updated: 2024/01/02 11:19:09 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	transfer_texture(t_textures *texture, t_map *map, t_map_color *color);
bool	not_allowed_chars(char *str);

void	process_line(t_textures *text, t_map *map, char *line, int *line_number)
{
	if (not_allowed_chars(line))
		ft_write_error("Error\nUsage of a not allowed character\n");
	else if (!is_empty_or_spaces(line) && !only_map_chars(line))
	{
		if (text->p_cl == 6)
			ft_write_error("Error\nNot allowed chars in map\n");
		else if (map->found_map && text->p_cl != 6)
			ft_write_error("Error\nMap bewtween path lines\n");
		text->p_cl++;
		process_textures(text, line);
	}
	else if (!is_empty_or_spaces(line) && only_map_chars(line))
	{
		if (text->p_cl == 6 && map->space_found == false)
		{
			map->found_map = true;
			process_map_line(map, line, line_number);
		}
		else if (text->p_cl != 6)
			ft_write_error("Error\nCan't find full path before map lines\n");
		else if (map->space_found == true)
			ft_write_error("Error\nSpaces between map lines\n");
	}
	else if (is_empty_or_spaces(line) && map->found_map)
		map->space_found = true;
}

void	ft_read_more_cub(t_map *map, t_textures *text, int line_number, int fd)
{
	process_texture_raw(text);
	map->map_end = line_number;
	set_measures_and_close(map, line_number, fd);
}

void	ft_read_cub(char **argv, t_textures *text, t_map *map)
{
	int		fd;
	char	*line;
	int		line_number;

	line_number = 0;
	text->path_found = false;
	map->space_found = false;
	map->found_map = false;
	text->p_cl = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		ft_write_error("Error\nReading lines of the map\n");
	while (line)
	{
		process_line(text, map, line, &line_number);
		free(line);
		line = get_next_line(fd);
	}
	if (map->found_map && text->path_found && text->p_cl == 6)
		ft_read_more_cub(map, text, line_number, fd);
	else
		ft_write_error("Error: No filled paths\n");
}

// void	print_everything(t_map *map, t_player *player,
// 		t_textures *texture, t_map_color *color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < map->max_height)
// 	{
// 		j = 0;
// 		while (j < map->max_width)
// 		{
// 			printf("%c", map->map_2d[i][j]);
// 			j++;
// 		}
// 		i++;
// 		printf("\n");
// 	}
// 	// printf("----------------------------------------------------\n");
// 	// printf("Player position on X and Y axes: %d and %d\n",
// 	// 	player->px, player->py);
// 	// printf("Player direction X axe: %d\n", player->dirx);
// 	// printf("Player direction Y axe: %d\n", player->diry);
// 	// printf("NO %s\n", texture->paths->north);
// 	// printf("SO %s\n", texture->paths->south);
// 	// printf("EA %s\n", texture->paths->east);
// 	// printf("WE %s\n", texture->paths->west);
// 	// printf("Ceil Color: %u\n", color->ceil_color->hex);
// 	// printf("Floor Color: %u\n", color->floor_color->hex);
// 	// printf("----------------------------------------------------\n");
// }

t_map	ft_start_map(char **argv)
{
	t_textures	texture;
	t_map_color	color;
	t_map		map;

	init_textures(&texture);
	init_color(&color);
	init_map(&map);
	ft_read_cub(argv, &texture, &map);
	get_color_floor(&color, &texture);
	get_color_ceil(&color, &texture);
	ft_check_color(&color);
	create_2d(&map);
	copy_line_to_map(&map);
	transfer_texture(&texture, &map, &color);
	get_player(&map);
	free_textures(&texture);
	free_mapcolor(&color);
	return (map);
}

void	transfer_texture(t_textures *texture, t_map *map, t_map_color *color)
{
	if (texture->paths->north)
		map->texture[0] = texture->paths->north;
	if (texture->paths->south)
		map->texture[1] = texture->paths->south;
	if (texture->paths->west)
		map->texture[2] = texture->paths->west;
	if (texture->paths->east)
		map->texture[3] = texture->paths->east;
	map->color_c[0] = color->ceil_color->r;
	map->color_c[1] = color->ceil_color->g;
	map->color_c[2] = color->ceil_color->b;
	map->color_f[0] = color->floor_color->r;
	map->color_f[1] = color->floor_color->g;
	map->color_f[2] = color->floor_color->b;
}
